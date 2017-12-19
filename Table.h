using namespace std;

class ISubtreeWrapper;

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

	Info(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :typ(_typ), name(_name),nestedInfo(_nestedInfo)
	{
		infoType = "info";
	}

	Info(const IType* _typ) :typ(_typ), nestedInfo({})
	{
		infoType = "info";
	}

	//������� ��� �������
	virtual const IType* GetType() const
	{
		return typ;
	}

	//������� ��� �������
	virtual const Symbol* GetName() const
	{
		return name;
	}

	//������� ��������� ����������
	virtual vector<const Info*> GetNestedInfo() const
	{
		vector<const Info*> nothing;
		return nothing;
	}

	//������� �������� ���� ����������
	virtual string GetInfoType() const
	{
		return infoType;
	}

	//������� �����
	virtual const IFrame* GetFrame() const
	{
		return nullptr;
	}

	//������� �����
	virtual const ISubtreeWrapper* GetTreeWrapper() const
	{
		return nullptr;
	}

	//���������� ��� ����������
	virtual void SetInfoType(string _infoType)
	{
		infoType = _infoType;
	}

	//�������� ���������� � nestedInfo
	virtual void PushNestedInfo(const Info* newInfo)
	{
	}

	//������ ��� ��������� ����������
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

//���������� � ������
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

	MethodInfo(const IType* _typ, const Symbol* _name, vector<const Info*> _nestedInfo) :Info(_typ, _name, _nestedInfo) 
	{
		infoType = "method";
	}

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

	VariableInfo(const IType* _typ, const Symbol* _name) :Info(_typ, _name, {})
	{
		infoType = "var";
	}

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

	ContainerInfo(vector<const Info*> _nestedInfo) :Info(nullptr, nullptr, _nestedInfo) 
	{
		infoType = "container";
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
class FrameInfo :public Info
{
public:

	FrameInfo(const Symbol* _name, const IFrame* _frame) : frame(_frame), Info(nullptr, _name, {})
	{
		infoType = "frame";
	}

	//������� �����
	const IFrame* GetFrame() const
	{
		return frame;
	}

private:
	const IFrame* frame;//���������� � ������

};

//���������� � IR-���������
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

	//������� ������� IR-���������
	virtual const ISubtreeWrapper* GetTreeWrapper() const
	{
		return wrapper;
	}

private:
	const ISubtreeWrapper* wrapper;//���������� �� IR-���������

};