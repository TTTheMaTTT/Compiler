
//���������, �������������� ��� �������� ������������ ���������� �������� ������
struct ClassHierarchy
{
	const Symbol* className;
	ClassHierarchy* parent;
	unordered_map<string, ClassHierarchy*> children;

	ClassHierarchy(const Symbol* _className) : className(_className) {};

	//�������� ������
	void AddChild(ClassHierarchy* _child)
	{
		children.insert({ _child->className->str, _child });
		_child->parent = this;
	}

	//����� ������
	ClassHierarchy* FindChild(const Symbol* childName)
	{
		auto element = children.find(childName->str);
		if (element != children.end())
			return element->second;
		else
			return nullptr;
	}

	//������ ������
	void RemoveChild(const Symbol* childName)
	{
		ClassHierarchy* child = FindChild(childName);
		if (child != nullptr)
		{
			child->parent = nullptr;
			children.erase(childName->str);
		}
	}

	//����� �������
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

	//�������� ������ ���� ������� ������ ������ �� ���� ������, ������� �� ������ �������� (�� �����).
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

		//������ �������� ������
		vector<const Symbol*> ancestors;
		for (auto iter = reversedAncestors.rbegin(); iter != reversedAncestors.rend(); iter++)
			ancestors.push_back(*iter);

		return ancestors;
	}

	//������� ���� �����
	void Clear()
	{
		children.clear();
		parent = nullptr;
	}

};

//����� ����������, ������� ��������� �������� �� ������� ������ �������������� �����
class TypeChecker : public IVisitor
{
public:

	TypeChecker(): cHierarchy(getIntern("root")){};

	//������ ������� ��������
	void SetSymbolTable(const Info* _symbolTable)
	{
		symbolTable = _symbolTable;
	}

	//����� ���������� ������������� ������ � �������� �� ���������� �������� ������� 
	rValue visit(const Program* n)
	{
		rValue r;
		fout = ofstream("TypeCheck.txt");
		
		fout << "�������� ������" << endl;

		const Info* myInfo = symbolTable;

		currentVarTable = new ContainerInfo({});
		InitializeTypes();//������������� ������ �����
		CreateClassHierarchy(symbolTable);//���������������� �������� �������
		
										  //������ ����� � �������� � ��������� �� ������������
		for (auto classDecl : n->classes)
		{
			if (classDecl->ext->line < 0)
				continue;//��������������� ����� �� �� ���� �� �����������
			int hierarchyOutput = CreateHierarchyBond(classDecl->name, classDecl->ext->parentClassName);
			if (hierarchyOutput == -2)
				fout << classDecl->ext->line << " - " << "����������� ���������� ����� " << 
																					classDecl->ext->parentClassName->str << endl;
			else if (hierarchyOutput==-1)
				fout << classDecl->ext->line << " - " << "����������� ����� " <<classDecl->name->str<<
										" �������� ������� ������������ ������ "<< classDecl->ext->parentClassName->str << endl;
		}

		CreateClassTable(symbolTable);//�������� �� ������� �������� ������� �������
		
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

		fout << "�������� ���������" << endl;

		fout.close();
		return r;
	}

	rValue visit(const IMainClass* n)
	{
		//��� ������� �������� �� ����������
		rValue table;

		//fout << "� � MainClass" <<endl;

		currentClassName = n->name;
		const Info* myInfo = pointInfo;

		n->statement->Accept(this);

		return table;
	}

	//����� ��������� ������������ ��� ���������� � �� ������������ ������� (����������� ������� ���) ������ � ������ �������
	rValue visit(const IClassDeclaration* n)
	{
		rValue table;

		currentClassName = n->name;
		const Info* myInfo = pointInfo;

		ClassHierarchy* classInHierarchy = cHierarchy.FindDescendant(myInfo->GetName());
		if (classInHierarchy == nullptr)
		{
			fout << n->line << " - " << "����� " << n->name->str <<" �� ����� � �������� �������! � ��� �������"<< endl;
		}

		if (classInHierarchy->parent != nullptr)
		{
			GetClassVars(classInHierarchy->parent);//��� ���������� ������� ��������� � checkedVars
			GetClassMethods(classInHierarchy->parent);//��� ������ ������� ��������� � checkedMethods
		}

		vector<const Info*> nestedInfo = myInfo->GetNestedInfo();
		int varSize = n->vars.size();
		//�������� �� ������������ ��� ����������� ����������
		for (int i = 0; i < varSize; i++)
		{
			const IVarDeclaration* var = n->vars[i];
			if (HaveVar(nestedInfo[i]->GetName()))
				fout << var->line << " - " << "���������� " <<var->name->str << 
											" ��� ���� � ������� ��������� ������ " <<n->name->str<< endl;
			else
				checkedVars.push_back(var->name);
		}

		//�������� �� ������������ ����������� ������� ������
		for (int i = 0; i < n->methods.size(); i++)
		{
			const IMethodDeclaration* method = n->methods[i];
			if (HaveMethod(nestedInfo[varSize+i]))
				fout << method->line << " - " << "����� " << method->name->str <<
							" � ���������� ����������� ��� ���� � ������� ��������� ������ " << n->name->str << endl;
			else
				checkedMethods.push_back(nestedInfo[varSize + i]);
		}

		//�������� ����������, ������� ��������� � ��������� � ������ ������
		AddToCurrentVarTable(GetClassVars(classInHierarchy));
		const Info* savedInfo = SaveVarTable();

		//�������� ������� �� ������� ������
		for (int i = 0; i < n->methods.size(); i++)
		{
			LoadVarTable(savedInfo);
			pointInfo = nestedInfo[varSize + i];
			n->methods[i]->Accept(this);
		}

		return table;
	}

	//��� ������ �������� �� �������������� ���
	rValue visit(const IVarDeclaration* n)
	{
		rValue table;

		const Info* myInfo = pointInfo;
		if (!TypeIsExisting(n->typ->typeName))
			fout << n->line << " - " << "����������� ��� " << n->typ->typeName->str <<" ���������� " << n->name->str << endl;

		return table;
	}

	//��� ������ �������� �� ������������ ��� ���������� � ���������� ������. 
	//� ����� ���������, ��� ������������ �������� ��������� �� ���� � �������.
	rValue visit(const IMethodDeclaration* n)
	{
		rValue table;

		const Info* myInfo = pointInfo;
		if (!TypeIsExisting(n->typ->typeName))
			fout << n->line << " - " << "����������� ��� " << n->typ->typeName->str << " ������ " << n->name->str << endl;

		checkedVars.clear();
		vector<const Info*> nestedInfo = myInfo->GetNestedInfo();
		int argSize = n->args.size();
		//�������� �� ������������ ��� ����������� ����������
		for (int i = 0; i < argSize; i++)
		{
			const IVarDeclaration* var = n->args[i];
			if (HaveVar(nestedInfo[i]->GetName()))
				fout << var->line << " - " << "���������� " << var->name->str <<
				" ��� ���� � ������� ��������� ������ " << n->name->str << endl;
			else
				checkedVars.push_back(var->name);
		}

		//�������� �� ������������ ��� ����������� ���������� ������
		for (int i = 0; i < n->vars.size(); i++)
		{
			const IVarDeclaration* var = n->vars[i];
			if (HaveVar(nestedInfo[argSize+i]->GetName()))
				fout << var->line << " - " << "���������� " << var->name->str <<
				" ��� ���� � ������� ��������� ������ " << n->name->str << endl;
			else
				checkedVars.push_back(var->name);
		}

		//�������� ����������, ������� ��������� � ��������� � ������ ������
		AddToCurrentVarTable(myInfo);
		const Info* savedInfo = SaveVarTable();

		//�������� ���������� �� ������� ������
		for (int i = 0; i < n->args.size(); i++)
		{
			//LoadVarTable(savedInfo); - �������, ��� ������� ��������� ������ ������ �� ��������
			pointInfo = nestedInfo[i];
			n->args[i]->Accept(this);
		}

		//�������� ���������� �� ������� ������
		for (int i = 0; i < n->vars.size(); i++)
		{
			//LoadVarTable(savedInfo); - �������, ��� ������� ��������� ������ ������ �� ��������
			pointInfo = nestedInfo[argSize+i];
			n->vars[i]->Accept(this);
		}

		//�������� ����������� �� ������� ������
		for (const IStatement* state: n->statements)
		{
			//LoadVarTable(savedInfo); - �������, ��� ������� ��������� ������ ������ �� ��������
			state->Accept(this);
		}

		if (n->typ->typeName!=n->e->Accept(this).info->GetType()->typeName)
			fout << n->e->line << " - " << "��� ������ " << n->name->str << " �� ������������� ���� ��� ������������� ��������"<< endl;

		return table;
	}

	//����� �������� �������� ���� ����������� ������ ����������
	rValue visit(const CompoundStatement* n)
	{
		rValue table;

		//�������� ����������� �� ������� ������
		for (const IStatement* state : n->statements)
			state->Accept(this);

		return table;
	}

	//�������� �� ��, ��� ��� if-�� ����� bool
	rValue visit(const ConditionalStatement* n)
	{
		rValue table;

		if (n->ifExp->Accept(this).info->GetType()->typeName!=getIntern("bool"))
			fout << n->ifExp->line << " - " << "�������� ��������� ������ ����� ��� bool" <<endl;

		n->thenState->Accept(this);
		n->elseState->Accept(this);

		return table;
	}

	//��� whil-�� ������ ������ bool
	rValue visit(const CycleStatement* n)
	{
		rValue table;

		if (n->conditionExp->Accept(this).info->GetType()->typeName != getIntern("bool"))
			fout << n->conditionExp->line << " - " << "������� ����� ������ ����� ��� bool" << endl;

		n->actionState->Accept(this);

		return table;
	}

	//�������� �� ��, ��� ��������� ���������
	rValue visit(const PrintStatement* n)
	{
		rValue table;

		//fout << "� � PrintStatement" << endl;
		const Symbol* printType = n->e->Accept(this).info->GetType()->typeName;
		if (printType!=getIntern("int") && printType != getIntern("bool") && printType != getIntern("String"))
			fout << n->e->line << " - " << "������ ������� ������ � ����� " <<printType->str<< endl;
		return table;
	}

	//�������� �� ������������ �����
	rValue visit(const AssignStatement* n)
	{
		rValue table;

		//���������, ���������� �� ���������� � �������� ������
		const Info* assignedVar = FindVarByName(n->varName);

		const Info* expInfo = n->e->Accept(this).info;
		if (assignedVar==nullptr)
			fout << n->line << " - " << "����������� ���������� " << n->varName->str << endl;
		else if (assignedVar->GetType()->typeName!=expInfo->GetType()->typeName)
			fout << n->line << " - " << "���� ���������� " << n->varName->str <<" � ����������� �� ��������� �� ���������"<< endl;

		return table;
	}
	
	//���������� ������ ���� �������� �����, ������ - ���, ��� � ������������� ���������
	rValue visit(const AssignArrayElementStatement* n)
	{
		rValue table;

		const Info* assignedVar = FindVarByName(n->varName);
		const Info* indexInfo = n->index->Accept(this).info;
		const Info* expInfo = n->e->Accept(this).info; 
		if (assignedVar == nullptr)
			fout << n->line << " - " << "����������� ���������� " << n->varName->str << endl;
		else
		{
			if (assignedVar->GetType()->typeName != getIntern("array of int"))
				fout << n->line << " - " << "��� ���������� " << n->varName->str << " �� ������������� ������" << endl;
			if (indexInfo->GetType()->typeName != getIntern("int"))
				fout << n->line << " - " << "��� ������� �� int" << endl;
			if (expInfo->GetType()->typeName != getIntern("int"))
				fout << n->line << " - " << "��� ����������� �������� �� int" << endl;
		}

		return table;
	}

	//��������� �� ������������ ��������� ������ �����
	rValue visit(const BinopExp* n)
	{
		rValue table;

		const Symbol* typeName1 = n->e1->Accept(this).info->GetType()->typeName;
		const Symbol* typeName2 = n->e2->Accept(this).info->GetType()->typeName;
		if (static_cast<int>(n->opType) < 4)//��������� �������������� ��������
		{
			if (typeName1 != typeName2 || typeName1 != getIntern("int"))
				fout << n->line << " - " << "�������������� �������� ������������ �� ��� int`���" << endl;
			table.info = new Info(new IType(getIntern("int")));
		}
		else if (static_cast<int>(n->opType) < 6)//And � or
		{
			if (typeName1 != typeName2 || typeName1 != getIntern("bool"))
				fout << n->line << " - " << "���������� ��������� ������������ �� �� bool'��" << endl;
			table.info = new Info(new IType(getIntern("bool")));
		}
		else if (static_cast<int>(n->opType) < 8)//<, >
		{
			if (typeName1 != typeName2 || typeName1 != getIntern("int"))
				fout << n->line << " - " << "��������� ������������ �� ��� int`���" << endl;
			table.info = new Info(new IType(getIntern("bool")));
		}
		else //==
		{
			if (typeName1 != typeName2)
				fout << n->line << " - " << "����������� ��������� �������� ������ ����� " <<
																				typeName1->str<<" � "<<typeName2->str<< endl;
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
			fout << n->line << " - " << "������ ���� " << typeName1->str << 
														" - �������� ��������������, ��� ������������� ������" << endl;

		if (typeName2 != getIntern("int"))
			fout << n->line << " - " << "������ �� �������� �����" << endl;

		table.info = new Info(new IType(getIntern("int")));

		return table;
	}

	rValue visit(const GetLengthExp* n)
	{
		rValue table;

		const Symbol* typeName = n->e1->Accept(this).info->GetType()->typeName;
		if (typeName != getIntern("array of int"))
			fout << n->line << " - " << "������ ������ ������ � ������� ���� " << typeName->str <<endl;

		table.info = new Info(new IType(getIntern("int")));

		return table;
	}

	rValue visit(const MethodExp* n)
	{
		rValue table;

		//fout << "� � MethodExp" << endl;

		//fout << "�������� ����������� ����� �������" << endl;
		const Info* objInfo = n->e1->Accept(this).info;
		//if (objInfo==nullptr)
			//fout << "���������� �� ������� ����������� " << endl;
		const IType* objType = objInfo->GetType();
		//if (objType == nullptr)
			//fout << "���������� � ���� ������� ����������� " << endl;
		const Symbol* typeName = objType->typeName;
		//if (typeName == nullptr)
			//fout << "���������� � �������� ���� ������� ����������� " << endl;
		//�������� �� ������������� ����
		
		//fout << "�������� �� ������������� ���� �������" << endl;
		if (!TypeIsExisting(typeName))
		{
			fout << n->line << " - " << "����� ���������� � ������� ������������ ���� " << typeName->str << endl;
			table.info = new Info(new IType(getIntern("unknown")));
			return table;
		}

		//�������� �� ������������� ������
		ClassHierarchy* _classHierarchy=cHierarchy.FindDescendant(typeName);
		if (_classHierarchy == nullptr)
		{
			fout << n->line << " - " << "����� ���������� � �������, �� ����������� �������" <<endl;
			table.info = new Info(new IType(getIntern("unknown")));
			return table;
		}

		const Info* methodsInfo = GetClassMethods(_classHierarchy);
		Info* argsInfo = new ContainerInfo({});
		
		//int i = 0;
		//fout << "���������� ������ ����������" << endl;
		for (const IExp* argExp : n->args)
		{
			const Info* argInfo = argExp->Accept(this).info;
			//fout <<i<< " " <<argInfo->GetType()->typeName->str <<" ";
			argsInfo->PushNestedInfo(argInfo);
			//i++;
		}
		//fout << endl;

		//fout << "���� ��������������� �����" << endl;
		const Info* methodInfo = FindMethodByName(methodsInfo, n->methodName, argsInfo);
		if (methodInfo == nullptr)
		{
			fout << n->line << " - " << "���������� �������������� ����� "<<n->methodName->str<<
																" ������ "<<_classHierarchy->className->str << endl;
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

		//���������, ���������� �� ���������� � �������� ������
		const Info* var = FindVarByName(n->id);

		if (var == nullptr)
		{
			fout << n->line << " - " << "���������� "<<n->id->str<< " �� ��������� � ������� ���������" << endl;
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
			fout << n->line << " - " << "������ ������ ������ ������� ����� " << typeName->str << endl;

		table.info = new Info(new IType(getIntern("array of int")));

		return table;
	}

	rValue visit(const NewObjectExp* n)
	{
		rValue table;

		//fout << "� � NewObjectExp" << endl;

		//�������� �� ������������� ����
		if (!TypeIsExisting(n->typName))
			fout << n->line << " - " << "�������� ������ ������������ ���� " << n->typName->str << endl;
		else
		{
			//�������� �� ������������� ������
			ClassHierarchy* _classHierarchy = cHierarchy.FindDescendant(n->typName);
			if (_classHierarchy == nullptr)
				fout << n->line << " - " << "�������� ������ ���� " << n->typName->str << ", �� ���������� �������" << endl;
		}

		table.info = new Info(new IType(n->typName));

		return table;
	}

	rValue visit(const NegativeExp* n)
	{
		rValue table;

		const Symbol* typeName = n->e1->Accept(this).info->GetType()->typeName;
		if (typeName != getIntern("bool"))
			fout << n->line << " - " << "������ ��������� ��������� �� ������� ���� " << typeName->str << endl;

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

	ofstream fout;//�������� �����, �� �������� ���������� ����� ����������

	const Info* symbolTable;//������� ���� �������� ���������
	const Info* pointInfo;//��������� �� ���������� ������� � ������� ��������

	Info* classTable;//���������� � ���� �������
	Info* currentVarTable;//������� ����������, ������������ � ������ ������
	const Symbol* currentClassName;//�����, ������� ����������� � ������ ������

	ClassHierarchy cHierarchy;//�������� ���� ������� ���������

	vector<const Symbol*> programTypes;//����, ������� ������������ � ���������
	vector<const Symbol*> checkedVars;//������ �������� ����������, ������� ������������ ��� ��������� ���������� ����������
	vector<const Info*> checkedMethods;//������ ���������� � ������, ������� ������������ ��� ��������� ���������� �������

	//������������� ������ �����
	void InitializeTypes()
	{
		programTypes.clear();
		programTypes.push_back(getIntern("int"));
		programTypes.push_back(getIntern("bool"));
		programTypes.push_back(getIntern("String"));
		programTypes.push_back(getIntern("array of int"));
		programTypes.push_back(getIntern("unknown"));
	}

	//�������� �� ������������� ����
	bool TypeIsExisting(const Symbol* typeName)
	{
		for (const Symbol* _typeName : programTypes)
			if (_typeName == typeName)
				return true;
		return false;
	}

	//�������� �� ������� � checedVars ����������� Symbol
	bool HaveVar(const Symbol* varName)
	{
		for (const Symbol* checkedVar : checkedVars)
			if (checkedVar == varName)
				return true;

		return false;
	}

	//��������� �������� ������� ��������
	void ClearSymbolTable()
	{
		currentVarTable = new ContainerInfo({});
	}

	//��������� ������� ������� �������� � ����� ��������� �� ��������� Info
	const Info* SaveVarTable()
	{
		return new ContainerInfo(currentVarTable->GetNestedInfo());
	}

	//��������� ������� �������� �� �������
	void LoadVarTable(const Info* _savedVarTable)
	{
		currentVarTable = new ContainerInfo(_savedVarTable->GetNestedInfo());
	}

	//������� �������� �������
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

	//������� ����� ����� ��������
	//���������� �������, ���� �� �������; 0, ���� childClass ��� ����� ��������; -1, ���� ���������� ��������; 
	//-2, ���� ������������� ������ �� ���������� 
	int CreateHierarchyBond(const Symbol* childClassName, const Symbol* parentClassName)
	{
		ClassHierarchy* childClass = cHierarchy.FindChild(childClassName);
		if (childClass == nullptr)//���� childClass ��� �������� ��������
			return 0;
		if (childClass->FindDescendant(parentClassName) != nullptr)//���� ������������ ����� �������� �������� ���������
			return -1;
		ClassHierarchy* parentClass = cHierarchy.FindDescendant(parentClassName);
		if (parentClass == nullptr)
			return -2;
		cHierarchy.RemoveChild(childClassName);
		parentClass->AddChild(childClass);
		return 1;
	}

	//������� ������� � ����������� ��� ���� �������, ������������ � ���������
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

	//������� ���������� � ������ � ������ ������
	const Info* FindClassInfo(const Symbol* className)
	{
		for (auto cInfo : classTable->GetNestedInfo())
		{
			if (cInfo->GetName() == className)
				return cInfo;
		}
		return nullptr;
	}

	//�������� ������ ����������, ������� ��������� � ������� ��������� ������� ������
	const Info* GetClassVars(ClassHierarchy* _cHierarchy)
	{
		Info* varsInfo = new ContainerInfo({});

		checkedVars.clear();

		vector<const Symbol*> classesNames =_cHierarchy->GetClassHierarchyLine();//�������� �������� ���� ������������ �������
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

	//�������� ���������� �� ���������� ���������� ������
	const Info* GetMethodArgs(const Info* methodInfo)
	{
		Info* argsInfo = new ContainerInfo({});
		for (auto argInfo : methodInfo->GetNestedInfo())
			if (argInfo->GetInfoType() == "arg")
				argsInfo->PushNestedInfo(argInfo);
		return argsInfo;
	}

	//�������� ��������� ���������� ������ � ��������� �������
	bool CompareMethodArgs(const Info* methodInfo, const Info* argsInfo)
	{
		//fout << "���������� ���������" << endl;
		vector<const Info*> methodArgs = methodInfo->GetNestedInfo();
		vector<const Info*> args = argsInfo->GetNestedInfo();
		if (methodArgs.size() != args.size())//��������� �� ������� ������� ����������
		{
			//fout << "������ ���������� �� ��������� �� �����" << endl;
			return false;
		}
		for (int i = 0; i < methodArgs.size(); i++)//���� ������ ���������� �������� ������, ������ ��� ���� ���� ������ ���������
			if (methodArgs[i]->GetType()->typeName != args[i]->GetType()->typeName)
			{
				//fout << "�������� ����" << methodArgs[i]->GetType()->typeName->str<< "�� ��������� � ���������� ���� "
				//																  << args[i]->GetType()->typeName->str<<endl;
				return false;
			}
		return true;
	}

	//�������� ��������� ���� �������
	bool CompareMethods(const Info* method1, const Info* method2)
	{
		return CompareMethodArgs(method1, GetMethodArgs(method2)) && method1->GetName()==method2->GetName();
	}

	//��������� ������� ���������� ������ � ������ checkedMethods
	bool HaveMethod(const Info* methodInfo)
	{
		for (const Info* _methodInfo : checkedMethods)
			if (CompareMethods(methodInfo, _methodInfo))
				return true;
		return false;
	}

	//������� ��� ������, ������� ����� �������� ��������� ������� ������
	const Info* GetClassMethods(ClassHierarchy* _cHierarchy)
	{
		Info* methodsInfo = new ContainerInfo({});
		checkedMethods.clear();

		vector<const Symbol*> classesNames= _cHierarchy->GetClassHierarchyLine();//�������� �������� ���� ������������ �������
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

	//�������� � ������� ������� ���������� ����� ������
	void AddToCurrentVarTable(const Info* addedInfo)
	{
		checkedVars.clear();

		for (auto addedVar : addedInfo->GetNestedInfo())
		{
			if (addedVar->GetInfoType() != "var" && addedVar->GetInfoType() != "arg")
				continue;//�� ��������� ���������� � ����������
			if (HaveVar(addedVar->GetName()))
				continue;//���� �� ��� �������� ������ ����������, �� ����������

			checkedVars.push_back(addedVar->GetName());
			
			//������, ���� ������ ���������� ��� ������������ ������ ������� ������� ���������� ��� �� ���� ����������,
			//�� �������������� ����������
			bool isOldVar = false;
			for (auto existedVar : currentVarTable->GetNestedInfo())
				if (existedVar->GetName() == addedVar->GetName())
				{
					existedVar = addedVar;
					isOldVar = true;
					break;
				}
			if (!isOldVar)
				currentVarTable->PushNestedInfo(addedVar);//����� ������� ������ ���������� ����� ����������
		}

	}

	//����� � ������� ������� ���������� ���������� � �������� ������
	const Info* FindVarByName(const Symbol* _varName)
	{
		for (auto _var : currentVarTable->GetNestedInfo())
			if (_var->GetName() == _varName)
				return _var;
		return nullptr;
	}

	//�� ��������� ������ ������� ����� ��� �����, ������� ����� �������� ��� � �������� ������ ����������
	const Info* FindMethodByName(const Info* _methodsInfo, const Symbol* _methodName, const Info* methodArgs)
	{
		//fout << "�������� ����� ������ " <<_methodName->str<< endl;
		//int i = 0;
		for (const Info* _method : _methodsInfo->GetNestedInfo())
		{
			//fout << i<<" " <<_method->GetName()->str<<endl;
			//if (_method->GetName()==_methodName)
				//fout << "����� ������� ���������" << endl;
			//if (CompareMethodArgs(_method, methodArgs))
				//fout << "��������� ������� ���������" << endl;
			if (_method->GetName() == _methodName && CompareMethodArgs(GetMethodArgs(_method), methodArgs))
				return _method;
			//i++;
		}
		return nullptr;
	}

};
