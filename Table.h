using namespace std;

extern Symbol* getIntern(const string& src);

//����������� �����, ������������ ��� ��������� �����
class Symbol {
public:
	string str;

	Symbol(const string& _str):str(_str) {}
	//Symbol(const Symbol&) = delete;
	//void operator=(const Symbol&) = delete;
};

//�����, ������������ ��� ����������� ����� ��������
class IType 
{
public:
	const Symbol* typeName;

	IType(const Symbol* symbol) :typeName(symbol) {}
	IType(string _str) {};
};

//���������� � ��������� �������� � ���������
class Info
{
public:

	Info(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :typ(_typ), name(_name), nestedInfo(_nestedInfo) {};

	//������� ��� �������
	virtual const IType* GetType() const
	{
		return nullptr;
	}

	//������� ��� �������
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

//���������� � ������
class ClassInfo :public Info
{
public:

	ClassInfo(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :Info(_typ,_name, _nestedInfo){}
	ClassInfo(const Symbol* _name, vector<const Info*> _nestedInfo) :Info(new IType(getIntern("Class")), _name, _nestedInfo) {}


	//������� ��� �������
	const IType* GetType() const
	{
		return typ;
	}

	//������� ��� �������
	const Symbol* GetName() const
	{
		return name;
	}

	//������� ���������� � ��������� ��������
	vector<const Info*> GetNestedInfo() const
	{
		return nestedInfo;
	}

	//������� ����� ����������
	void PushNestedInfo(const Info* newInfo)
	{
		nestedInfo.push_back(newInfo);
	}

};

//���������� � ������
class MethodInfo :public Info
{
public:

	MethodInfo(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :Info(_typ, _name, _nestedInfo) {}

	//������� ��� �������
	const IType* GetType() const
	{
		return typ;
	}

	//������� ��� �������
	const Symbol* GetName() const
	{
		return name;
	}

	//������� ���������� � ��������� ��������
	vector<const Info*> GetNestedInfo() const
	{
		return nestedInfo;
	}

	//������� ����� ����������
	void PushNestedInfo(const Info* newInfo)
	{
		nestedInfo.push_back(newInfo);
	}
};

//���������� � ����������
class VariableInfo :public Info
{
public:

	VariableInfo(const IType* _typ, const Symbol* _name) :Info(_typ, _name, {}) {}

	//������� ��� �������
	const IType* GetType() const
	{
		return typ;
	}

	//������� ��� �������
	const Symbol* GetName() const
	{
		return name;
	}
};

//���������� � ���������� ��������� ����������
class ContainerInfo :public Info
{
public:

	ContainerInfo(vector<const Info*> _nestedInfo) :Info(nullptr, nullptr, _nestedInfo) {}

	//������� ���������� � ��������� ��������
	vector<const Info*> GetNestedInfo() const
	{
		return nestedInfo;
	}

	//������� ����� ����������
	void PushNestedInfo(const Info* newInfo)
	{
		nestedInfo.push_back(newInfo);
	}
};