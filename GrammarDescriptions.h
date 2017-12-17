using namespace std;

/*
//���������, ������� ��������� �� ������ � ������� � ������������� ����
struct Position
{
	int line;
	int pos;

	Position(int _line, int _pos) : line(_line), pos(_pos) {};
};
*/

//���������, � ������� �������� ���������� � ������������
struct Extension
{
	const Symbol* parentClassName;
	const int line;

	Extension() :line(-1) {};
	Extension(const Symbol* _parentClassName, const int _line) : parentClassName(_parentClassName), line(_line) {};
};

#pragma region Lists

#pragma region ClassDeclarationList

//��������� ������ ���������� �������
class IClassDeclarationList
{
public:
	vector<const IClassDeclaration *> classes;
	IClassDeclarationList() {};
	IClassDeclarationList(const IClassDeclarationList* _classList) :classes(_classList->classes) {};
};

//������ ���������� ������� � ����� ����������� � �������
class AddClassDeclarationList : public IClassDeclarationList
{
public:

	AddClassDeclarationList(const IClassDeclarationList* _classList, const IClassDeclaration* _c) : IClassDeclarationList(_classList)
	{
		classes.push_back(_c);
	}
};

//������ ������ ���������� �������
class EmptyClassDeclarationList : public IClassDeclarationList
{
public:
	EmptyClassDeclarationList() {}
};

#pragma endregion

#pragma region VarDeclarationList

//������ ����������
class IVarDeclarationList
{
public:
	vector<const IVarDeclaration*> vars;
	IVarDeclarationList() {};
	IVarDeclarationList(const IVarDeclarationList* _varList) : vars(_varList->vars) {}
};

//������ ���������� ���������� � ����� ����������� � �������
class AddVarDeclarationList : public IVarDeclarationList
{
public:
	AddVarDeclarationList(const IVarDeclarationList* _varList, const IVarDeclaration* _v) : IVarDeclarationList(_varList)
	{
		vars.push_back(_v);
	}
};

//������ ������ ���������� ����������
class EmptyVarDeclarationList : public IVarDeclarationList
{
public:
	EmptyVarDeclarationList() {}
};

#pragma endregion

#pragma region MethodDeclarationList

//������ �������
class IMethodDeclarationList
{
public:
	vector<const IMethodDeclaration*> methods;
	IMethodDeclarationList() {};
	IMethodDeclarationList(const IMethodDeclarationList* _methodList) : methods(_methodList->methods) {};
};

//������ ���������� ������� � ����� ����������� � �������
class AddMethodDeclarationList : public IMethodDeclarationList
{
public:

	AddMethodDeclarationList(const IMethodDeclarationList* _methodList, const IMethodDeclaration* _m) : IMethodDeclarationList(_methodList)
	{
		methods.push_back(_m);
	}

};

//������ ������ ���������� �������
class EmptyMethodDeclarationList : public IMethodDeclarationList
{
public:
	EmptyMethodDeclarationList() {}
};

#pragma endregion

#pragma region StatementList

//��������� ������ �����������
class IStatementList
{
public:
	vector<const IStatement*> statements;
	IStatementList() {};
	IStatementList(const IStatementList* _stateList) : statements(_stateList->statements) {};
};

//������ ����������� � ����� ������������ � �������
class AddStatementList : public IStatementList
{
public:

	AddStatementList(const IStatement* _s, const IStatementList* _stateList)
	{
		statements.push_back(_s);
		for (auto state : _stateList->statements)
			statements.push_back(state);
	}

};

//������ ������ ���������� �������
class EmptyStatementList : public IStatementList
{
public:
	EmptyStatementList() {}
};

//������ ����������� � �������������� ������� � �������
class ErrorStatementList : public IStatementList
{
public:

	ErrorStatementList(const IStatementList* _stateList) : IStatementList(_stateList) {}
};

#pragma endregion

#pragma region ExpressionList

//��������� ������ �����������
class IExpList {
public:
	vector<const IExp*> exps;
};

//������ ��������� � �������
class AddExpList : public IExpList {

public:

	AddExpList(const IExp* _e1, const IExpList *_eList)
	{
		exps.push_back(_e1);
		for (auto exp : _eList->exps)
			exps.push_back(exp);
	}

};

//������ ���������, ��������� �� ������ ��������
class OnlyExpList : public IExpList {

public:
	const IExp* e1;

	OnlyExpList(const IExp* _e1)
	{
		exps.push_back(_e1);
	}

};

//������ ������ ���������
class ZeroExpList : public IExpList {

public:

	ZeroExpList() {}

};

#pragma endregion

#pragma endregion

#pragma region SyntaxClasses

//���������
class Program
{
public:
	string text;
	const IMainClass *mClass;
	vector<const IClassDeclaration *> classes;

	Program(const IMainClass* _mClass, const IClassDeclarationList* _classList) :mClass(_mClass), classes(_classList->classes) {};

};

//������� �����
class IMainClass
{
public:

	const Symbol* name;
	const Symbol* argName;//��� ��������� ������� main ���� String[]
	const IStatement* statement;

	IMainClass(const Symbol* _name, const Symbol* _argName, const IStatement* _statement) : 
																name(_name), argName(_argName), statement(_statement) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//��������� ���������� ������
class IClassDeclaration
{
public:
	const Symbol* name;
	const Extension* ext;
	vector<const IVarDeclaration*> vars;
	vector<const IMethodDeclaration*> methods;	
	const int line;

	IClassDeclaration(const Symbol* _name, const Extension* _ext, 
					const IVarDeclarationList* _varList,const IMethodDeclarationList* _methodList, const int _line) :
					name(_name),ext(_ext),vars(_varList->vars), methods(_methodList->methods), line(_line) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//��������� ���������� ����������
class IVarDeclaration
{
public:

	const IType* typ;
	const Symbol* name;
	const int line;

	IVarDeclaration(const IType* _typ, const Symbol* _name, const int _line):typ(_typ), name(_name), line(_line) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region ArgumentList

//��������� ������ ����������
class IArgumentList
{
public:
	vector<const IVarDeclaration*> args;
};

//������ ���������� � �������
class AddArgumentList : public IArgumentList
{

public:

	AddArgumentList(const IType* _typ, const Symbol* _name, const IArgumentList* _argList, const int _line)
	{
		args.push_back(new IVarDeclaration(_typ, _name, _line));
		vector<const IVarDeclaration*> addedArgs = _argList->args;
		for (auto arg : addedArgs)
			args.push_back(arg);
	}

};

//���� ��������
class OnlyArgumentList : public IArgumentList
{
public:

	OnlyArgumentList(const IType* _typ, const Symbol* _name, const int _line)
	{
		args.push_back(new IVarDeclaration(_typ, _name,_line));
	}
};

//������ ������ ����������
class ZeroArgumentList : public IArgumentList {

public:

	ZeroArgumentList() {}

};

#pragma endregion

//��������� ���������� ������
class IMethodDeclaration
{
public:

	const IType* typ;
	const Symbol* name;
	vector<const IVarDeclaration*> args;
	vector<const IVarDeclaration*> vars;
	vector<const IStatement*> statements;
	const IExp* e;
	const int line;

	IMethodDeclaration(const IType* _typ, const Symbol* _name, const IArgumentList* _argList, const IVarDeclarationList* _varList,
		const IStatementList* _stateList, const IExp* _e, int _line) :
		typ(_typ), name(_name), args(_argList->args), vars(_varList->vars), statements(_stateList->statements), e(_e), line(_line) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region Statement

//��������� �����������
class IStatement
{
public:
	const int line;
	IStatement(const int _line) : line(_line) {};
	virtual rValue Accept(IVisitor *v) const = 0;
};

//��������� �����������
class CompoundStatement : public IStatement
{
public:
	vector<const IStatement*> statements;

	CompoundStatement(const IStatementList* _stateList, const int _line) :IStatement(_line),statements(_stateList->statements) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//�������
class ConditionalStatement : public IStatement
{
public:
	const IExp* ifExp;
	const IStatement* thenState;
	const IStatement* elseState;

	ConditionalStatement(const IExp* _ifExp, const IStatement* _thenState, const IStatement* _elseState, const int _line) :
												IStatement(_line), ifExp(_ifExp), thenState(_thenState), elseState(_elseState) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//����
class CycleStatement :public IStatement
{
public:
	const IExp* conditionExp;
	const IStatement* actionState;

	CycleStatement(const IExp* _conditionExp, const IStatement* _actionState, const int _line) :IStatement(_line),
																		conditionExp(_conditionExp), actionState(_actionState) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//������
class PrintStatement :public IStatement
{
public:
	const IExp* e;

	PrintStatement(const IExp* _e, const int _line) :IStatement(_line), e(_e) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//�������������
class AssignStatement :public IStatement
{
public:
	const Symbol* varName;
	const IExp* e;

	AssignStatement(const Symbol* _varName, const IExp* _e, const int _line) :IStatement(_line), varName(_varName), e(_e) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//������������ �������� �������
class AssignArrayElementStatement :public IStatement
{
public:
	const Symbol* varName;
	const IExp* e;
	const IExp* index;

	AssignArrayElementStatement(const Symbol* _varName, const IExp* _index, const IExp* _e, const int _line) :IStatement(_line),
																						varName(_varName), index(_index), e(_e) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

#pragma region Expression

//��������� ���������
class IExp {
public:
	const int line;
	IExp(const int _line) :line(_line) {};
	IExp(): line(-1) {};
	virtual rValue Accept(IVisitor *v) const = 0;
};

//��������� ��������
class TernExp : public IExp {
public:

	const IExp *e1, *e2, *e3;

	TernExp(const IExp *_e1, const IExp *_e2, const IExp *_e3) :e1(_e1), e2(_e2), e3(_e3) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//�������� ��������
class BinopExp : public IExp {
public:

	const IExp *e1, *e2;
	binOpType opType;

	BinopExp(const IExp *_e1, const IExp *_e2, const int _line, binOpType _opType) :IExp(_line),e1(_e1), e2(_e2), opType(_opType){}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//����������� �������� �������
class GetArrayElementExp : public IExp {
public:

	const IExp *e1, *e2;

	GetArrayElementExp(const IExp *_e1, const IExp *_e2, const int _line) :IExp(_line), e1(_e1), e2(_e2) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//������� ������ �������
class GetLengthExp : public IExp
{
public:
	const IExp *e1;
	GetLengthExp(const IExp *_e1, const int _line) :IExp(_line), e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//������� �����
class MethodExp : public IExp
{
public:

	const IExp *e1;
	const Symbol* methodName;
	vector<const IExp*> args;

	MethodExp(const IExp *_e1, const Symbol* _methodName, const IExpList* _eList, const int _line) :
								IExp(_line), methodName(_methodName),e1(_e1),args(_eList->exps) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//�������� ���������
class NumExp : public IExp {
public:

	const int num;

	NumExp(const int _num, const int _line) :IExp(_line), num(_num) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//������ ���������
class BoolExp : public IExp {
public:

	const bool flag;

	BoolExp(const bool _flag, const int _line) :IExp(_line), flag(_flag) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//�������������
class IDExp : public IExp {
public:

	const Symbol* id;

	IDExp(const Symbol* _id, const int _line) :IExp(_line), id(_id) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//��������� �� �������� �������
class ThisExp : public IExp {
public:

	ThisExp() {}


	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//��������� �������
class GetArrayExp : public IExp {
public:

	const IExp *e1;

	GetArrayExp(const IExp *_e1, const int _line) :IExp(_line), e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//�������� ������ �������
class NewObjectExp : public IExp
{
public:

	const Symbol* typName;//�������� ���� ������������ �������

	NewObjectExp(const Symbol* _typName, const int _line) :IExp(_line), typName(_typName) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//��������� �����������
class NegativeExp : public IExp {
public:

	const IExp *e1;

	NegativeExp(const IExp *_e1, const int _line) :IExp(_line), e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//��������� ���������
class EnclosedExp : public IExp
{
public:

	const IExp *e1;
	EnclosedExp(const IExp *_e1, const int _line) :IExp(_line), e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

#pragma endregion