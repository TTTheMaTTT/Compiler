using namespace std;

class ISubtreeWrapper;

extern Symbol* getIntern(const string& src);

//Специальный класс, используемый для сравнения строк
class Symbol {
public:
	string str;

	Symbol(const string& _str):str(_str) {}
	//Symbol(const Symbol&) = delete;
	//void operator=(const Symbol&) = delete;
};

//Класс, используемый для обозначения типов объектов
class IType 
{
public:
	const Symbol* typeName;

	IType(const Symbol* symbol) :typeName(symbol) {}
	IType(string _str) {};
};

//Информация о различных объектах в программе
class Info
{
public:

	Info(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :typ(_typ), name(_name),nestedInfo(_nestedInfo)
	{
		infoType = "info";
	}

	Info(const IType* _typ) :typ(_typ), nestedInfo({})
	{
		infoType = "info";
	}

	//Вернуть тип объекта
	virtual const IType* GetType() const
	{
		return typ;
	}

	//Вернуть имя объекта
	virtual const Symbol* GetName() const
	{
		return name;
	}

	//Вернуть вложенную информацию
	virtual vector<const Info*> GetNestedInfo() const
	{
		vector<const Info*> nothing;
		return nothing;
	}

	//Вернуть название типа информации
	virtual string GetInfoType() const
	{
		return infoType;
	}

	//Вернуть фрейм
	virtual const IFrame* GetFrame() const
	{
		return nullptr;
	}

	//Вернуть фрейм
	virtual const ISubtreeWrapper* GetTreeWrapper() const
	{
		return nullptr;
	}

	//Установить тип информации
	virtual void SetInfoType(string _infoType)
	{
		infoType = _infoType;
	}

	//Добавить информацию в nestedInfo
	virtual void PushNestedInfo(const Info* newInfo)
	{
	}

	//Убрать всю вложенную информацию
	virtual void ClearNestedInfo()
	{
		nestedInfo.clear();
	}

protected:

	string infoType;
	const IType* typ;
	const Symbol* name;
	vector<const Info*> nestedInfo;
};

//Информация о классе
class ClassInfo :public Info
{
public:

	ClassInfo(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :Info(_typ, _name, _nestedInfo) 
	{ 
		infoType = "class"; 
	}

	ClassInfo(const Symbol* _name, vector<const Info*> _nestedInfo) :Info(new IType(getIntern("Class")), _name, _nestedInfo)
	{
		infoType = "class";
	}


	//Вернуть тип объекта
	const IType* GetType() const
	{
		return typ;
	}

	//Вернуть имя объекта
	const Symbol* GetName() const
	{
		return name;
	}

	//Вернуть информацию о вложенных объектах
	vector<const Info*> GetNestedInfo() const
	{
		return nestedInfo;
	}

	//Вложить новую информацию
	void PushNestedInfo(const Info* newInfo)
	{
		nestedInfo.push_back(newInfo);
	}

};

//Информация о методе
class MethodInfo :public Info
{
public:

	MethodInfo(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :Info(_typ, _name, _nestedInfo) 
	{
		infoType = "method";
	}

	//Вернуть тип объекта
	const IType* GetType() const
	{
		return typ;
	}

	//Вернуть имя объекта
	const Symbol* GetName() const
	{
		return name;
	}

	//Вернуть информацию о вложенных объектах
	vector<const Info*> GetNestedInfo() const
	{
		return nestedInfo;
	}

	//Вложить новую информацию
	void PushNestedInfo(const Info* newInfo)
	{
		nestedInfo.push_back(newInfo);
	}
};

//Информация о переменной
class VariableInfo :public Info
{
public:

	VariableInfo(const IType* _typ, const Symbol* _name) :Info(_typ, _name, {})
	{
		infoType = "var";
	}

	//Вернуть тип объекта
	const IType* GetType() const
	{
		return typ;
	}

	//Вернуть имя объекта
	const Symbol* GetName() const
	{
		return name;
	}
};

//Информация о контейнере различной информации
class ContainerInfo :public Info
{
public:

	ContainerInfo(vector<const Info*> _nestedInfo) :Info(nullptr, nullptr, _nestedInfo) 
	{
		infoType = "container";
	}

	//Вернуть информацию о вложенных объектах
	vector<const Info*> GetNestedInfo() const
	{
		return nestedInfo;
	}

	//Вложить новую информацию
	void PushNestedInfo(const Info* newInfo)
	{
		nestedInfo.push_back(newInfo);
	}
};

//Информация о фрейме
class FrameInfo :public Info
{
public:

	FrameInfo(const Symbol* _name, const IFrame* _frame) : frame(_frame), Info(nullptr, _name, {})
	{
		infoType = "frame";
	}

	//Вернуть фрейм
	const IFrame* GetFrame() const
	{
		return frame;
	}

private:
	const IFrame* frame;//Информация о фрейме

};

//Информация о IR-поддереве
class SubtreeWrapperInfo :public Info
{
public:

	SubtreeWrapperInfo(const ISubtreeWrapper* _wrapper) : wrapper(_wrapper), Info(nullptr, nullptr, {})
	{
		infoType = "IR subtree";
	}

	SubtreeWrapperInfo(const IType* typ, const ISubtreeWrapper* _wrapper) : wrapper(_wrapper), Info(typ, nullptr, {})
	{
		infoType = "IR subtree";
	}

	//Вернуть враппер IR-поддерева
	virtual const ISubtreeWrapper* GetTreeWrapper() const
	{
		return wrapper;
	}

private:
	const ISubtreeWrapper* wrapper;//Информация об IR-поддереве

};