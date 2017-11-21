
//Структура, использующуюся для проверки правильности построения иерархии класса
struct ClassHierarchy
{
	const Symbol* className;
	ClassHierarchy* parent;
	unordered_map<string, ClassHierarchy*> children;

	ClassHierarchy(const Symbol* _className) : className(_className) {};

	//Добавить ребёнка
	void AddChild(ClassHierarchy* _child)
	{
		children.insert({ _child->className->str, _child });
		_child->parent = this;
	}

	//Найти ребёнка
	ClassHierarchy* FindChild(const Symbol* childName)
	{
		auto element = children.find(childName->str);
		if (element != children.end())
			return element->second;
		else
			return nullptr;
	}

	//Убрать ребёнка
	void RemoveChild(const Symbol* childName)
	{
		ClassHierarchy* child = FindChild(childName);
		if (child != nullptr)
		{
			child->parent = nullptr;
			children.erase(childName->str);
		}
	}

	//Найти потомка
	ClassHierarchy* FindDescendant(const Symbol* childName)
	{
		ClassHierarchy* descendant = nullptr;
		auto element = children.find(childName->str);
		if (element != children.end())
			descendant = element->second;
		else
			for (auto iter = children.begin(); iter != children.end(); iter++)
			{
				descendant = iter->second->FindDescendant(childName);
				if (descendant != nullptr)
					break;
			}
		return descendant;
	}

	//Получить список всех предков класса вплоть до него самого, начиная от самого древнего (не корня).
	vector<const Symbol*> GetClassHierarchyLine() const
	{
		vector<const Symbol*> reversedAncestors;
		ClassHierarchy* currentClass = this->parent;
		reversedAncestors.push_back(className);
		while (currentClass != nullptr && currentClass->className!=getIntern("root"))
		{
			reversedAncestors.push_back(currentClass->className);
			currentClass = currentClass->parent;
		}

		//Теперь развернём список
		vector<const Symbol*> ancestors;
		for (auto iter = reversedAncestors.rbegin(); iter != reversedAncestors.rend(); iter++)
			ancestors.push_back(*iter);

		return ancestors;
	}

	//Удалить всех детей
	void Clear()
	{
		children.clear();
		parent = nullptr;
	}

};

//Класс посетителя, который проверяет сущности на наличие ошибок несоответствия типов
class TypeChecker : public IVisitor
{
public:

	TypeChecker(): cHierarchy(getIntern("root")){};

	//Задать таблицу символов
	void SetSymbolTable(const Info* _symbolTable)
	{
		symbolTable = _symbolTable;
	}

	//Здесь проводятся инициализация чекера и проверки на правильную иерархию классов 
	rValue visit(const Program* n)
	{
		rValue r;
		fout = ofstream("TypeCheck.txt");
		
		fout << "Проверка начата" << endl;

		const Info* myInfo = symbolTable;

		currentVarTable = new ContainerInfo({});
		InitializeTypes();//Инициализация списка типов
		CreateClassHierarchy(symbolTable);//Инициализировать иерархию классов
		
										  //Создаём связи в иерархии и проверяем их правильность
		for (auto classDecl : n->classes)
		{
			if (classDecl->ext->line < 0)
				continue;//Рассматриваемый класс ни от кого не наследуется
			int hierarchyOutput = CreateHierarchyBond(classDecl->name, classDecl->ext->parentClassName);
			if (hierarchyOutput == -2)
				fout << classDecl->ext->line << " - " << "Неизвестный наследумый класс " << 
																					classDecl->ext->parentClassName->str << endl;
			else if (hierarchyOutput==-1)
				fout << classDecl->ext->line << " - " << "Наследующий класс " <<classDecl->name->str<<
										" является предком наследуемого класса "<< classDecl->ext->parentClassName->str << endl;
		}

		CreateClassTable(symbolTable);//Выделяем из таблицы символов таблицу классов
		
		ClearSymbolTable();
		vector<const Info*> classesInfos = myInfo->GetNestedInfo();

		pointInfo = classesInfos[0];
		n->mClass->Accept(this);

		for (int i = 1; i < classesInfos.size(); i++)
		{
			ClearSymbolTable();
			pointInfo = classesInfos[i];
			n->classes[i-1]->Accept(this);
		}

		ClearSymbolTable();

		fout << "Проверка закончена" << endl;

		fout.close();
		return r;
	}

	rValue visit(const IMainClass* n)
	{
		//Тут никаких проверок не происходит
		rValue table;

		//fout << "Я в MainClass" <<endl;

		currentClassName = n->name;
		const Info* myInfo = pointInfo;

		n->statement->Accept(this);

		return table;
	}

	//Здесь проверяем уникальность имён переменных и на уникальность методов (виртуальных методов нет) класса с учётом предков
	rValue visit(const IClassDeclaration* n)
	{
		rValue table;

		currentClassName = n->name;
		const Info* myInfo = pointInfo;

		ClassHierarchy* classInHierarchy = cHierarchy.FindDescendant(myInfo->GetName());
		if (classInHierarchy == nullptr)
		{
			fout << n->line << " - " << "Класс " << n->name->str <<" не попал в иерархию классов! И это странно"<< endl;
		}

		if (classInHierarchy->parent != nullptr)
		{
			GetClassVars(classInHierarchy->parent);//Все переменные предков занесутся в checkedVars
			GetClassMethods(classInHierarchy->parent);//Все методы предков занесутся в checkedMethods
		}

		vector<const Info*> nestedInfo = myInfo->GetNestedInfo();
		int varSize = n->vars.size();
		//Проверка на уникальность имён объявленных переменных
		for (int i = 0; i < varSize; i++)
		{
			const IVarDeclaration* var = n->vars[i];
			if (HaveVar(nestedInfo[i]->GetName()))
				fout << var->line << " - " << "переменная " <<var->name->str << 
											" уже есть в области видимости класса " <<n->name->str<< endl;
			else
				checkedVars.push_back(var->name);
		}

		//Проверка на уникальность объявленных методов класса
		for (int i = 0; i < n->methods.size(); i++)
		{
			const IMethodDeclaration* method = n->methods[i];
			if (HaveMethod(nestedInfo[varSize+i]))
				fout << method->line << " - " << "метод " << method->name->str <<
							" с указанными аргументами уже есть в области видимости класса " << n->name->str << endl;
			else
				checkedMethods.push_back(nestedInfo[varSize + i]);
		}

		//Запомним переменные, которые находятся в видимости в данный момент
		AddToCurrentVarTable(GetClassVars(classInHierarchy));
		const Info* savedInfo = SaveVarTable();

		//Проверка методов на наличие ошибок
		for (int i = 0; i < n->methods.size(); i++)
		{
			LoadVarTable(savedInfo);
			pointInfo = nestedInfo[varSize + i];
			n->methods[i]->Accept(this);
		}

		return table;
	}

	//Тут делаем проверку на несуществующий тип
	rValue visit(const IVarDeclaration* n)
	{
		rValue table;

		const Info* myInfo = pointInfo;
		if (!TypeIsExisting(n->typ->typeName))
			fout << n->line << " - " << "Неизвестный тип " << n->typ->typeName->str <<" переменной " << n->name->str << endl;

		return table;
	}

	//Тут делаем проверку на уникальность имён переменных и аргументов метода. 
	//А также проверяем, что возвращаемое значение совпадает по типу с методом.
	rValue visit(const IMethodDeclaration* n)
	{
		rValue table;

		const Info* myInfo = pointInfo;
		if (!TypeIsExisting(n->typ->typeName))
			fout << n->line << " - " << "Неизвестный тип " << n->typ->typeName->str << " метода " << n->name->str << endl;

		checkedVars.clear();
		vector<const Info*> nestedInfo = myInfo->GetNestedInfo();
		int argSize = n->args.size();
		//Проверка на уникальность имён объявленных аргументов
		for (int i = 0; i < argSize; i++)
		{
			const IVarDeclaration* var = n->args[i];
			if (HaveVar(nestedInfo[i]->GetName()))
				fout << var->line << " - " << "переменная " << var->name->str <<
				" уже есть в области видимости метода " << n->name->str << endl;
			else
				checkedVars.push_back(var->name);
		}

		//Проверка на уникальность имён объявленных переменных метода
		for (int i = 0; i < n->vars.size(); i++)
		{
			const IVarDeclaration* var = n->vars[i];
			if (HaveVar(nestedInfo[argSize+i]->GetName()))
				fout << var->line << " - " << "переменная " << var->name->str <<
				" уже есть в области видимости метода " << n->name->str << endl;
			else
				checkedVars.push_back(var->name);
		}

		//Запомним переменные, которые находятся в видимости в данный момент
		AddToCurrentVarTable(myInfo);
		const Info* savedInfo = SaveVarTable();

		//Проверка аргументов на наличие ошибок
		for (int i = 0; i < n->args.size(); i++)
		{
			//LoadVarTable(savedInfo); - считаем, что область видимости внутри метода не меняется
			pointInfo = nestedInfo[i];
			n->args[i]->Accept(this);
		}

		//Проверка переменных на наличие ошибок
		for (int i = 0; i < n->vars.size(); i++)
		{
			//LoadVarTable(savedInfo); - считаем, что область видимости внутри метода не меняется
			pointInfo = nestedInfo[argSize+i];
			n->vars[i]->Accept(this);
		}

		//Проверка утверждений на наличие ошибок
		for (const IStatement* state: n->statements)
		{
			//LoadVarTable(savedInfo); - считаем, что область видимости внутри метода не меняется
			state->Accept(this);
		}

		if (n->typ->typeName!=n->e->Accept(this).info->GetType()->typeName)
			fout << n->e->line << " - " << "Тип метода " << n->name->str << " не соответствует типу его возвращаемого значения"<< endl;

		return table;
	}

	//Здесь проводим проверку всех утверждений внутри составного
	rValue visit(const CompoundStatement* n)
	{
		rValue table;

		//Проверка утверждений на наличие ошибок
		for (const IStatement* state : n->statements)
			state->Accept(this);

		return table;
	}

	//Проверка на то, что под if-ом стоит bool
	rValue visit(const ConditionalStatement* n)
	{
		rValue table;

		if (n->ifExp->Accept(this).info->GetType()->typeName!=getIntern("bool"))
			fout << n->ifExp->line << " - " << "условное выражение должно иметь тип bool" <<endl;

		n->thenState->Accept(this);
		n->elseState->Accept(this);

		return table;
	}

	//Под whil-ом должен стоять bool
	rValue visit(const CycleStatement* n)
	{
		rValue table;

		if (n->conditionExp->Accept(this).info->GetType()->typeName != getIntern("bool"))
			fout << n->conditionExp->line << " - " << "условие цикла должно иметь тип bool" << endl;

		n->actionState->Accept(this);

		return table;
	}

	//Проверка на то, что выводится выводимое
	rValue visit(const PrintStatement* n)
	{
		rValue table;

		//fout << "Я в PrintStatement" << endl;
		const Symbol* printType = n->e->Accept(this).info->GetType()->typeName;
		if (printType!=getIntern("int") && printType != getIntern("bool") && printType != getIntern("String"))
			fout << n->e->line << " - " << "Нельзя вывести объект с типом " <<printType->str<< endl;
		return table;
	}

	//Проверка на соответствие типов
	rValue visit(const AssignStatement* n)
	{
		rValue table;

		//Определим, существует ли переменная с заданным именем
		const Info* assignedVar = FindVarByName(n->varName);

		const Info* expInfo = n->e->Accept(this).info;
		if (assignedVar==nullptr)
			fout << n->line << " - " << "Неизвестная переменная " << n->varName->str << endl;
		else if (assignedVar->GetType()->typeName!=expInfo->GetType()->typeName)
			fout << n->line << " - " << "Типы переменной " << n->varName->str <<" и присваемого ей выражения не совпадают"<< endl;

		return table;
	}
	
	//Переменная должна быть массивом интов, индекс - инт, как и присваиваемое выражение
	rValue visit(const AssignArrayElementStatement* n)
	{
		rValue table;

		const Info* assignedVar = FindVarByName(n->varName);
		const Info* indexInfo = n->index->Accept(this).info;
		const Info* expInfo = n->e->Accept(this).info; 
		if (assignedVar == nullptr)
			fout << n->line << " - " << "Неизвестная переменная " << n->varName->str << endl;
		else
		{
			if (assignedVar->GetType()->typeName != getIntern("array of int"))
				fout << n->line << " - " << "Тип переменной " << n->varName->str << " не целочисленный массив" << endl;
			if (indexInfo->GetType()->typeName != getIntern("int"))
				fout << n->line << " - " << "Тип индекса не int" << endl;
			if (expInfo->GetType()->typeName != getIntern("int"))
				fout << n->line << " - " << "Тип присваемого значения не int" << endl;
		}

		return table;
	}

	//Проверяем на соответствие операндов нужным типам
	rValue visit(const BinopExp* n)
	{
		rValue table;

		const Symbol* typeName1 = n->e1->Accept(this).info->GetType()->typeName;
		const Symbol* typeName2 = n->e2->Accept(this).info->GetType()->typeName;
		if (static_cast<int>(n->opType) < 4)//совершаем арифметическое действие
		{
			if (typeName1 != typeName2 || typeName1 != getIntern("int"))
				fout << n->line << " - " << "Арифметическое действие производится не над int`ами" << endl;
			table.info = new Info(new IType(getIntern("int")));
		}
		else if (static_cast<int>(n->opType) < 6)//And и or
		{
			if (typeName1 != typeName2 || typeName1 != getIntern("bool"))
				fout << n->line << " - " << "Логическое выражение составляется не из bool'ов" << endl;
			table.info = new Info(new IType(getIntern("bool")));
		}
		else if (static_cast<int>(n->opType) < 8)//<, >
		{
			if (typeName1 != typeName2 || typeName1 != getIntern("int"))
				fout << n->line << " - " << "Сравнение производится не над int`ами" << endl;
			table.info = new Info(new IType(getIntern("bool")));
		}
		else //==
		{
			if (typeName1 != typeName2)
				fout << n->line << " - " << "Проверяется равенство объектов разных типов " <<
																				typeName1->str<<" и "<<typeName2->str<< endl;
			table.info = new Info(new IType(getIntern("bool")));
		}

		return table;
	}

	rValue visit(const GetArrayElementExp* n)
	{
		rValue table;

		const Symbol* typeName1 = n->e1->Accept(this).info->GetType()->typeName;
		const Symbol* typeName2 = n->e2->Accept(this).info->GetType()->typeName;
		if (typeName1!=getIntern("array of int"))
			fout << n->line << " - " << "Объект типа " << typeName1->str << 
														" - ошибочно воспринимается, как целочисленный массив" << endl;

		if (typeName2 != getIntern("int"))
			fout << n->line << " - " << "Индекс не является интом" << endl;

		table.info = new Info(new IType(getIntern("int")));

		return table;
	}

	rValue visit(const GetLengthExp* n)
	{
		rValue table;

		const Symbol* typeName = n->e1->Accept(this).info->GetType()->typeName;
		if (typeName != getIntern("array of int"))
			fout << n->line << " - " << "Нельзя узнать размер у объекта типа " << typeName->str <<endl;

		table.info = new Info(new IType(getIntern("int")));

		return table;
	}

	rValue visit(const MethodExp* n)
	{
		rValue table;

		//fout << "Я в MethodExp" << endl;

		//fout << "Проверка вызывающего метод объекта" << endl;
		const Info* objInfo = n->e1->Accept(this).info;
		//if (objInfo==nullptr)
			//fout << "Информация об объекте отсутствует " << endl;
		const IType* objType = objInfo->GetType();
		//if (objType == nullptr)
			//fout << "Информация о типе объекта отсутствует " << endl;
		const Symbol* typeName = objType->typeName;
		//if (typeName == nullptr)
			//fout << "Информация о названии типа объекта отсутствует " << endl;
		//Проверка на существование типа
		
		//fout << "Проверка на существование типа объекта" << endl;
		if (!TypeIsExisting(typeName))
		{
			fout << n->line << " - " << "метод вызывается у объекта неизвестного типа " << typeName->str << endl;
			table.info = new Info(new IType(getIntern("unknown")));
			return table;
		}

		//Проверка на существование класса
		ClassHierarchy* _classHierarchy=cHierarchy.FindDescendant(typeName);
		if (_classHierarchy == nullptr)
		{
			fout << n->line << " - " << "метод вызывается у объекта, не являющегося классом" <<endl;
			table.info = new Info(new IType(getIntern("unknown")));
			return table;
		}

		const Info* methodsInfo = GetClassMethods(_classHierarchy);
		Info* argsInfo = new ContainerInfo({});
		
		//int i = 0;
		//fout << "Составляем список аргументов" << endl;
		for (const IExp* argExp : n->args)
		{
			const Info* argInfo = argExp->Accept(this).info;
			//fout <<i<< " " <<argInfo->GetType()->typeName->str <<" ";
			argsInfo->PushNestedInfo(argInfo);
			//i++;
		}
		//fout << endl;

		//fout << "Ищем соответствующий метод" << endl;
		const Info* methodInfo = FindMethodByName(methodsInfo, n->methodName, argsInfo);
		if (methodInfo == nullptr)
		{
			fout << n->line << " - " << "вызывается несуществующий метод "<<n->methodName->str<<
																" класса "<<_classHierarchy->className->str << endl;
			table.info = new Info(new IType(getIntern("unknown")));
			return table;
		}

		table.info = new Info(methodInfo->GetType());
		return table;
	}

	rValue visit(const NumExp* n)
	{
		rValue table;
		table.info = new Info(new IType(getIntern("int")));
		return table;
	}

	rValue visit(const BoolExp* n)
	{
		rValue table;
		table.info = new Info(new IType(getIntern("bool")));
		return table;
	}

	rValue visit(const IDExp* n)
	{
		rValue table;

		//Определим, существует ли переменная с заданным именем
		const Info* var = FindVarByName(n->id);

		if (var == nullptr)
		{
			fout << n->line << " - " << "Переменная "<<n->id->str<< " не находится в области видимости" << endl;
			table.info = new Info(new IType(getIntern("unknown")));
			return table;
		}

		table.info = new Info(var->GetType());

		return table;
	}

	rValue visit(const ThisExp* n)
	{
		rValue table;
		table.info = new Info(new IType(currentClassName));
		return table;
	}

	rValue visit(const GetArrayExp* n)
	{
		rValue table;

		const Symbol* typeName = n->e1->Accept(this).info->GetType()->typeName;
		if (typeName != getIntern("int"))
			fout << n->line << " - " << "Нельзя задать размер массива типом " << typeName->str << endl;

		table.info = new Info(new IType(getIntern("array of int")));

		return table;
	}

	rValue visit(const NewObjectExp* n)
	{
		rValue table;

		//fout << "Я в NewObjectExp" << endl;

		//Проверка на существование типа
		if (!TypeIsExisting(n->typName))
			fout << n->line << " - " << "создаётся объект неизвестного типа " << n->typName->str << endl;
		else
		{
			//Проверка на существование класса
			ClassHierarchy* _classHierarchy = cHierarchy.FindDescendant(n->typName);
			if (_classHierarchy == nullptr)
				fout << n->line << " - " << "создаётся объект типа " << n->typName->str << ", не являющийся классом" << endl;
		}

		table.info = new Info(new IType(n->typName));

		return table;
	}

	rValue visit(const NegativeExp* n)
	{
		rValue table;

		const Symbol* typeName = n->e1->Accept(this).info->GetType()->typeName;
		if (typeName != getIntern("bool"))
			fout << n->line << " - " << "Нельзя построить отрицание на объекте типа " << typeName->str << endl;

		table.info = new Info(new IType(getIntern("bool")));
		return table;
	}

	rValue visit(const EnclosedExp* n)
	{
		rValue table;
		table.info = new Info(n->e1->Accept(this).info->GetType());
		return table;
	}

private:

	ofstream fout;//Файловый поток, по которому происходит вывод информации

	const Info* symbolTable;//Таблица всех символов программы
	const Info* pointInfo;//Указатель на конкретную позицию в таблице символов

	Info* classTable;//Информация о всех классах
	Info* currentVarTable;//Таблица переменных, используемых в данный момент
	const Symbol* currentClassName;//Класс, который проверяется в данный момент

	ClassHierarchy cHierarchy;//Иерархия всех классов программы

	vector<const Symbol*> programTypes;//Типы, которые используются в программе
	vector<const Symbol*> checkedVars;//Список названий переменных, который используется для избежания повторения переменных
	vector<const Info*> checkedMethods;//Список информаций о методе, который используется для избежания повторения методов

	//Инициализация списка типов
	void InitializeTypes()
	{
		programTypes.clear();
		programTypes.push_back(getIntern("int"));
		programTypes.push_back(getIntern("bool"));
		programTypes.push_back(getIntern("String"));
		programTypes.push_back(getIntern("array of int"));
		programTypes.push_back(getIntern("unknown"));
	}

	//Проверка на существование типа
	bool TypeIsExisting(const Symbol* typeName)
	{
		for (const Symbol* _typeName : programTypes)
			if (_typeName == typeName)
				return true;
		return false;
	}

	//Проверка на наличие в checedVars конкретного Symbol
	bool HaveVar(const Symbol* varName)
	{
		for (const Symbol* checkedVar : checkedVars)
			if (checkedVar == varName)
				return true;

		return false;
	}

	//Полностью очистить таблицу символов
	void ClearSymbolTable()
	{
		currentVarTable = new ContainerInfo({});
	}

	//Сохраняем текущую таблицу символов в новом указателе на структуру Info
	const Info* SaveVarTable()
	{
		return new ContainerInfo(currentVarTable->GetNestedInfo());
	}

	//Загружаем таблицу символов из резерва
	void LoadVarTable(const Info* _savedVarTable)
	{
		currentVarTable = new ContainerInfo(_savedVarTable->GetNestedInfo());
	}

	//Создать иерархию классов
	void CreateClassHierarchy(const Info *inf)
	{
		cHierarchy.Clear();
		for (auto cInfo : inf->GetNestedInfo())
		{
			if (cInfo->GetInfoType() != "class")
				continue;
			if (cHierarchy.FindChild(cInfo->GetName()) == nullptr)
				cHierarchy.AddChild(new ClassHierarchy(cInfo->GetName()));
		}
	}

	//Создать связь между классами
	//Возвращает единицу, если всё успешно; 0, если childClass уже имеет родителя; -1, если нарушается иерархия; 
	//-2, если родительского класса не существует 
	int CreateHierarchyBond(const Symbol* childClassName, const Symbol* parentClassName)
	{
		ClassHierarchy* childClass = cHierarchy.FindChild(childClassName);
		if (childClass == nullptr)//если childClass уже является дочерним
			return 0;
		if (childClass->FindDescendant(parentClassName) != nullptr)//Если родительский класс является потомком дочернего
			return -1;
		ClassHierarchy* parentClass = cHierarchy.FindDescendant(parentClassName);
		if (parentClass == nullptr)
			return -2;
		cHierarchy.RemoveChild(childClassName);
		parentClass->AddChild(childClass);
		return 1;
	}

	//Создать таблицу с информацией обо всех классах, используемых в программе
	void CreateClassTable(const Info* inf)
	{
		classTable = new ContainerInfo({});
		//int i = 0;
		for (auto cInfo : inf->GetNestedInfo())
		{
			if (FindClassInfo(cInfo->GetName()) == nullptr)
			{
				classTable->PushNestedInfo(cInfo);
				programTypes.push_back(cInfo->GetName());
			}
			//i++;
		}
	}

	//Вернуть информацию о классе с данным именем
	const Info* FindClassInfo(const Symbol* className)
	{
		for (auto cInfo : classTable->GetNestedInfo())
		{
			if (cInfo->GetName() == className)
				return cInfo;
		}
		return nullptr;
	}

	//Получить список переменных, которые находятся в области видимости данного класса
	const Info* GetClassVars(ClassHierarchy* _cHierarchy)
	{
		Info* varsInfo = new ContainerInfo({});

		checkedVars.clear();

		vector<const Symbol*> classesNames =_cHierarchy->GetClassHierarchyLine();//Получить названия всех родительских классов
		for (const Symbol* className : classesNames)
		{
			const Info* cInfo = FindClassInfo(className);
			if (cInfo == nullptr)
				continue;
			for (const Info* varInfo : cInfo->GetNestedInfo())
			{
				if (varInfo->GetInfoType() != "var")
					continue;
				if (HaveVar(varInfo->GetName()))
					continue;
				varsInfo->PushNestedInfo(varInfo);
				checkedVars.push_back(varInfo->GetName());
			}
		}

		return varsInfo;
	}

	//Получить информацию об аргументах указанного метода
	const Info* GetMethodArgs(const Info* methodInfo)
	{
		Info* argsInfo = new ContainerInfo({});
		for (auto argInfo : methodInfo->GetNestedInfo())
			if (argInfo->GetInfoType() == "arg")
				argsInfo->PushNestedInfo(argInfo);
		return argsInfo;
	}

	//Сравнить аргументы указанного метода с указанным списком
	bool CompareMethodArgs(const Info* methodInfo, const Info* argsInfo)
	{
		//fout << "Сравниваем аргументы" << endl;
		vector<const Info*> methodArgs = methodInfo->GetNestedInfo();
		vector<const Info*> args = argsInfo->GetNestedInfo();
		if (methodArgs.size() != args.size())//Сравнение по размеру списков аргументов
		{
			//fout << "Списки аргументов не совпадают по длине" << endl;
			return false;
		}
		for (int i = 0; i < methodArgs.size(); i++)//Если список аргументов подходит методу, значит все типы тоже должны совпадать
			if (methodArgs[i]->GetType()->typeName != args[i]->GetType()->typeName)
			{
				//fout << "Аргумент типа" << methodArgs[i]->GetType()->typeName->str<< "не совпадает с аргументом типа "
				//																  << args[i]->GetType()->typeName->str<<endl;
				return false;
			}
		return true;
	}

	//Сравнить аргументы двух методов
	bool CompareMethods(const Info* method1, const Info* method2)
	{
		return CompareMethodArgs(method1, GetMethodArgs(method2)) && method1->GetName()==method2->GetName();
	}

	//Проверить наличие указанного метода в списке checkedMethods
	bool HaveMethod(const Info* methodInfo)
	{
		for (const Info* _methodInfo : checkedMethods)
			if (CompareMethods(methodInfo, _methodInfo))
				return true;
		return false;
	}

	//Вернуть все методы, которые может вызывать экземпляр данного класса
	const Info* GetClassMethods(ClassHierarchy* _cHierarchy)
	{
		Info* methodsInfo = new ContainerInfo({});
		checkedMethods.clear();

		vector<const Symbol*> classesNames= _cHierarchy->GetClassHierarchyLine();//Получить названия всех родительских классов
		for (const Symbol* className : classesNames)
		{
			const Info* cInfo = FindClassInfo(className);
			if (cInfo == nullptr)
				continue;
			for (const Info* methodInfo : cInfo->GetNestedInfo())
			{
				if (methodInfo->GetInfoType() != "method")
					continue;
				if (HaveMethod(methodInfo))
					continue;
				methodsInfo->PushNestedInfo(methodInfo);
				checkedMethods.push_back(methodInfo);
			}
		}
		return methodsInfo;
	}

	//Добавить к текущей таблице переменных новую порцию
	void AddToCurrentVarTable(const Info* addedInfo)
	{
		checkedVars.clear();

		for (auto addedVar : addedInfo->GetNestedInfo())
		{
			if (addedVar->GetInfoType() != "var" && addedVar->GetInfoType() != "arg")
				continue;//Не добавляем информацию о переменной
			if (HaveVar(addedVar->GetName()))
				continue;//Если мы уже добавили данную переменную, то пропускаем

			checkedVars.push_back(addedVar->GetName());
			
			//Однако, если данная переменная уже существовала внутри текущей таблицы переменных ещё до всех добавлений,
			//то перезаписываем информацию
			bool isOldVar = false;
			for (auto existedVar : currentVarTable->GetNestedInfo())
				if (existedVar->GetName() == addedVar->GetName())
				{
					existedVar = addedVar;
					isOldVar = true;
					break;
				}
			if (!isOldVar)
				currentVarTable->PushNestedInfo(addedVar);//Самый обычный случай добавления новой переменной
		}

	}

	//Найти в текущей таблице переменных переменную с заданным именем
	const Info* FindVarByName(const Symbol* _varName)
	{
		for (auto _var : currentVarTable->GetNestedInfo())
			if (_var->GetName() == _varName)
				return _var;
		return nullptr;
	}

	//Из заданного списка методов найти тот метод, который имеет заданное имя и заданный список аргументов
	const Info* FindMethodByName(const Info* _methodsInfo, const Symbol* _methodName, const Info* methodArgs)
	{
		//fout << "Начинаем поиск метода " <<_methodName->str<< endl;
		//int i = 0;
		for (const Info* _method : _methodsInfo->GetNestedInfo())
		{
			//fout << i<<" " <<_method->GetName()->str<<endl;
			//if (_method->GetName()==_methodName)
				//fout << "Имена методов совпадают" << endl;
			//if (CompareMethodArgs(_method, methodArgs))
				//fout << "Аргументы методов совпадают" << endl;
			if (_method->GetName() == _methodName && CompareMethodArgs(GetMethodArgs(_method), methodArgs))
				return _method;
			//i++;
		}
		return nullptr;
	}

};
