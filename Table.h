using namespace std;

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

	Info(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :typ(_typ), name(_name), nestedInfo(_nestedInfo) {};

	//Вернуть тип объекта
	virtual const IType* GetType() const
	{
		return nullptr;
	}

	//Вернуть имя объекта
	virtual const Symbol* GetName() const
	{
		return nullptr;
	}

	virtual vector<const Info*> GetNestedInfo() const
	{
		vector<const Info*> nothing;
		return nothing;
	}

	virtual void PushNestedInfo(const Info* newInfo)
	{
	}

protected:
	const IType* typ;
	const Symbol* name;
	vector<const Info*> nestedInfo;
};

//Информация о классе
class ClassInfo :public Info
{
public:

	ClassInfo(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :Info(_typ,_name, _nestedInfo){}
	ClassInfo(const Symbol* _name, vector<const Info*> _nestedInfo) :Info(new IType(getIntern("Class")), _name, _nestedInfo) {}


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

	MethodInfo(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :Info(_typ, _name, _nestedInfo) {}

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

	VariableInfo(const IType* _typ, const Symbol* _name) :Info(_typ, _name, {}) {}

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

	ContainerInfo(vector<const Info*> _nestedInfo) :Info(nullptr, nullptr, _nestedInfo) {}

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