using namespace std;

#pragma region SyntaxClasses

//Программа
class Program
{
public:
	string text;
	const IMainClass *mClass;
	const IClassDeclarationList *classList;

	Program(const IMainClass* _mClass, const IClassDeclarationList* _classList) :mClass(_mClass), classList(_classList) {};

};

//Главный класс
class IMainClass
{
public:

	const Symbol* name;
	const Symbol* argName;//Имя аргумента функции main типа String[]
	const IStatement* statement;

	IMainClass(const Symbol* _name, const Symbol* _argName, const IStatement* _statement) : 
																name(_name), argName(_argName), statement(_statement) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region ClassDeclarationList

//Интерфейс списка объявлений классов
class IClassDeclarationList
{
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Список объявлений классов с одним объявлением и хвостом
class AddClassDeclarationList : public IClassDeclarationList
{
public:
	const IClassDeclarationList* classList;
	const IClassDeclaration* c;

	AddClassDeclarationList(const IClassDeclarationList* _classList, const IClassDeclaration* _c) : classList(_classList), c(_c) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Пустой список объявлений классов
class EmptyClassDeclarationList : public IClassDeclarationList
{
public:
	EmptyClassDeclarationList() {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

//Интерфейс объявления класса
class IClassDeclaration
{
public:
	const Symbol* name;
	const IVarDeclarationList* varList;
	const IMethodDeclarationList* methodList;

	IClassDeclaration(const Symbol* _name, const IVarDeclarationList* _varList, const IMethodDeclarationList* _methodList) :
																								name(_name),varList(_varList), methodList(_methodList) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region VarDeclarationList

//Список переменных
class IVarDeclarationList
{
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Список объявлений переменных с одним объявлением и хвостом
class AddVarDeclarationList : public IVarDeclarationList
{
public:
	const IVarDeclarationList* varList;
	const IVarDeclaration* var;

	AddVarDeclarationList(const IVarDeclarationList* _varList, const IVarDeclaration* _v) : varList(_varList), var(_v) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Пустой список объявлений переменных
class EmptyVarDeclarationList : public IVarDeclarationList
{
public:
	EmptyVarDeclarationList() {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

//Интерфейс объявления переменной
class IVarDeclaration
{
public:

	const IType* typ;
	const Symbol* name;

	IVarDeclaration(const IType* _typ, const Symbol* _name):typ(_typ), name(_name) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region MethodDeclarationList

//Список методов
class IMethodDeclarationList
{
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Список объявлений методов с одним объявлением и хвостом
class AddMethodDeclarationList : public IMethodDeclarationList
{
public:
	const IMethodDeclarationList* methodList;
	const IMethodDeclaration* m;

	AddMethodDeclarationList(const IMethodDeclarationList* _methodList, const IMethodDeclaration* _m) : methodList(_methodList), m(_m) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Пустой список объявлений методов
class EmptyMethodDeclarationList : public IMethodDeclarationList
{
public:
	EmptyMethodDeclarationList() {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

//Интерфейс объявления метода
class IMethodDeclaration
{
public:

	const IType* typ;
	const Symbol* name;
	const IArgumentList* argList;
	const IVarDeclarationList* varList;
	const IStatementList* stateList;
	const IExp* e;

	IMethodDeclaration(const IType* _typ, const Symbol* _name, const IArgumentList* _argList, const IVarDeclarationList* _varList, 
						const IStatementList* _stateList, const IExp* _e) :
						typ(_typ), name(_name),argList(_argList), varList(_varList), stateList(_stateList), e(_e) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region ArgumentList

//Интерфейс списка аргументов
class IArgumentList
{
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Список аргументов с хвостом
class AddArgumentList : public IArgumentList
{

public:

	const IType* typ;
	const Symbol* name;
	const IArgumentList* argList;

	AddArgumentList(const IType* _typ, const Symbol* _name, const IArgumentList* _argList) :typ(_typ), name(_name), argList(_argList) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Один аргумент
class OnlyArgumentList : public IArgumentList
{
public:

	const IType* typ;
	const Symbol* name;

	OnlyArgumentList(const IType* _typ, const Symbol* _name):typ(_typ), name(_name) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Пустой список аргументов
class ZeroArgumentList : public IArgumentList {

public:

	ZeroArgumentList() {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

#pragma endregion

#pragma region StatementList

//Интерфейс списка утверждений
class IStatementList
{
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Список утверждений с одним утверждением и хвостом
class AddStatementList : public IStatementList
{
public:
	const IStatement* s;
	const IStatementList* stateList;

	AddStatementList(const IStatement* _s, const IStatementList* _stateList) : stateList(_stateList), s(_s) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Пустой список объявлений методов
class EmptyStatementList : public IStatementList
{
public:
	EmptyStatementList() {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

#pragma region Statement

//Интерфейс утверждения
class IStatement
{
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Составное утверждение
class CompoundStatement : public IStatement
{
public:
	const IStatementList* stateList;

	CompoundStatement(const IStatementList* _stateList) :stateList(_stateList) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Условие
class ConditionalStatement : public IStatement
{
public:
	const IExp* ifExp;
	const IStatement* thenState;
	const IStatement* elseState;

	ConditionalStatement(const IExp* _ifExp, const IStatement* _thenState, const IStatement* _elseState) :ifExp(_ifExp), thenState(_thenState), elseState(_elseState) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Цикл
class CycleStatement :public IStatement
{
public:
	const IExp* conditionExp;
	const IStatement* actionState;

	CycleStatement(const IExp* _conditionExp, const IStatement* _actionState) :conditionExp(_conditionExp), actionState(_actionState) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Печать
class PrintStatement :public IStatement
{
public:
	const IExp* e;

	PrintStatement(const IExp* _e) :e(_e) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Инициализация
class AssignStatement :public IStatement
{
public:
	const Symbol* varName;
	const IExp* e;

	AssignStatement(const Symbol* _varName, const IExp* _e) :varName(_varName), e(_e) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Присваивание элемента массива
class AssignArrayElementStatement :public IStatement
{
public:
	const Symbol* varName;
	const IExp* e;
	const IExp* index;

	AssignArrayElementStatement(const Symbol* _varName, const IExp* _index, const IExp* _e) :varName(_varName), index(_index), e(_e) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

#pragma region ExpressionList

//Интерфейс списка утверждений
class IExpList {
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Список выражений с хвостом
class AddExpList : public IExpList {

public:

	const IExp* e1;
	const IExpList* eList;

	AddExpList(const IExp* _e1, const IExpList *_eList) :e1(_e1), eList(_eList) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Список выражений, состоящий из одного элемента
class OnlyExpList : public IExpList {

public:
	const IExp* e1;

	OnlyExpList(const IExp* _e1) :e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Пустой список выражений
class ZeroExpList : public IExpList {

public:

	ZeroExpList() {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

#pragma endregion

#pragma region Expression

//Интерфейс выражения
class IExp {
public:
	virtual rValue Accept(IVisitor *v) const = 0;
};

//Бинарная операция
class BinopExp : public IExp {
public:

	const IExp *e1, *e2;

	BinopExp(const IExp *_e1, const IExp *_e2) :e1(_e1), e2(_e2) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Возвращение элемента массива
class GetArrayElementExp : public IExp {
public:

	const IExp *e1, *e2;

	GetArrayElementExp(const IExp *_e1, const IExp *_e2) :e1(_e1), e2(_e2) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Вернуть размер массива
class GetLengthExp : public IExp
{
public:
	const IExp *e1;
	GetLengthExp(const IExp *_e1) :e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Вызвать метод
class MethodExp : public IExp
{
public:

	const IExp *e1;
	const Symbol* methodName;
	const IExpList *eList;

	MethodExp(const IExp *_e1, const Symbol* _methodName, const IExpList* _eList) :methodName(_methodName),e1(_e1), eList(_eList) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Числовое выражение
class NumExp : public IExp {
public:

	const int num;

	NumExp(const int _num) :num(_num) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Булево выражение
class BoolExp : public IExp {
public:

	const bool flag;

	BoolExp(const bool _flag) :flag(_flag) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Идентификатор
class IDExp : public IExp {
public:

	const Symbol* id;

	IDExp(const Symbol* _id):id(_id) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Указатель на активный элемент
class ThisExp : public IExp {
public:

	ThisExp() {}


	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Получение массива
class GetArrayExp : public IExp {
public:

	const IExp *e1;

	GetArrayExp(const IExp *_e1) :e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Создание нового объекта
class NewObjectExp : public IExp
{
public:

	const Symbol* typName;//Название типа создаваемого объекта

	NewObjectExp(const Symbol* _typName): typName(_typName) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Отрицание утверждения
class NegativeExp : public IExp {
public:

	const IExp *e1;

	NegativeExp(const IExp *_e1) : e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Свёрточное выражение
class EnclosedExp : public IExp
{
public:

	const IExp *e1;
	EnclosedExp(const IExp *_e1) :e1(_e1) {}

	rValue Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

#pragma endregion