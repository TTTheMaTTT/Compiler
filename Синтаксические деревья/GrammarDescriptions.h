#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GrammarDeclarations.h"
using namespace std;

//Класс посетителя
class IVisitor
{
public:
	virtual string visit(const Program* n)=0;
	virtual string visit(const IMainClass* n)=0;
	virtual string visit(const AddClassDeclarationList* n) = 0;
	virtual string visit(const EmptyClassDeclarationList* n) = 0;
	virtual string visit(const IClassDeclaration* n) = 0;
	virtual string visit(const AddVarDeclarationList* n) = 0;
	virtual string visit(const EmptyVarDeclarationList* n) = 0;
	virtual string visit(const IVarDeclaration* n) = 0;
	virtual string visit(const AddMethodDeclarationList* n) = 0;
	virtual string visit(const EmptyMethodDeclarationList* n) = 0;
	virtual string visit(const IMethodDeclaration* n) = 0;
	virtual string visit(const AddArgumentList* n) = 0;
	virtual string visit(const OnlyArgumentList* n) = 0;
	virtual string visit(const ZeroArgumentList* n) = 0;
	virtual string visit(const AddStatementList* n) = 0;
	virtual string visit(const EmptyStatementList* n) = 0;
	virtual string visit(const CompoundStatement* n) = 0;
	virtual string visit(const ConditionalStatement* n) = 0;
	virtual string visit(const CycleStatement* n) = 0;
	virtual string visit(const PrintStatement* n) = 0;
	virtual string visit(const AssignStatement* n) = 0;
	virtual string visit(const AssignArrayElementStatement* n) = 0;
	virtual string visit(const AddExpList* n) = 0;
	virtual string visit(const OnlyExpList* n) = 0;
	virtual string visit(const ZeroExpList* n) = 0;
	virtual string visit(const BinopExp* n) = 0;
	virtual string visit(const GetArrayElementExp* n) = 0;
	virtual string visit(const GetLengthExp* n) = 0;
	virtual string visit(const MethodExp* n) = 0;
	virtual string visit(const NumExp* n) = 0;
	virtual string visit(const BoolExp* n) = 0;
	virtual string visit(const IDExp* n) = 0;
	virtual string visit(const ThisExp* n) = 0;
	virtual string visit(const GetArrayExp* n) = 0;
	virtual string visit(const NewObjectExp* n) = 0;
	virtual string visit(const NegativeExp* n) = 0;
	virtual string visit(const EnclosedExp* n) = 0;
};

#pragma region SyntaxClasses

//Программа
class Program
{
public:
	string text;
	const IMainClass *mClass;
	const IClassDeclarationList *classList;

	Program(const IMainClass* _mClass, const IClassDeclarationList* _classList) :mClass(_mClass), classList(_classList){};

};

//Главный класс
class IMainClass
{
public:

	const IStatement* statement;

	IMainClass(const IStatement* _statement) : statement(_statement) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region ClassDeclarationList

//Интерфейс списка объявлений классов
class IClassDeclarationList
{
public:
	virtual string Accept(IVisitor *v) const = 0;
};

//Список объявлений классов с одним объявлением и хвостом
class AddClassDeclarationList : public IClassDeclarationList
{
public:
	const IClassDeclarationList* classList;
	const IClassDeclaration* c;

	AddClassDeclarationList(const IClassDeclarationList* _classList, const IClassDeclaration* _c) : classList(_classList), c(_c) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Пустой список объявлений классов
class EmptyClassDeclarationList : public IClassDeclarationList
{
public:
	EmptyClassDeclarationList() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

//Интерфейс объявления класса
class IClassDeclaration
{
public:
	const IVarDeclarationList* varList;
	const IMethodDeclarationList* methodList;

	IClassDeclaration(const IVarDeclarationList* _varList, const IMethodDeclarationList* _methodList) :varList(_varList), methodList(_methodList) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region VarDeclarationList

//Список переменных
class IVarDeclarationList
{
public:
	virtual string Accept(IVisitor *v) const = 0;
};

//Список объявлений переменных с одним объявлением и хвостом
class AddVarDeclarationList : public IVarDeclarationList
{
public:
	const IVarDeclarationList* varList;
	const IVarDeclaration* var;

	AddVarDeclarationList(const IVarDeclarationList* _varList, const IVarDeclaration* _v) : varList(_varList), var(_v) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Пустой список объявлений переменных
class EmptyVarDeclarationList : public IVarDeclarationList
{
public:
	EmptyVarDeclarationList() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

//Интерфейс объявления переменной
class IVarDeclaration
{
public:

	IVarDeclaration() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region MethodDeclarationList

//Список методов
class IMethodDeclarationList
{
public:
	virtual string Accept(IVisitor *v) const = 0;
};

//Список объявлений методов с одним объявлением и хвостом
class AddMethodDeclarationList : public IMethodDeclarationList
{
public:
	const IMethodDeclarationList* methodList;
	const IMethodDeclaration* m;

	AddMethodDeclarationList(const IMethodDeclarationList* _methodList, const IMethodDeclaration* _m) : methodList(_methodList), m(_m) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Пустой список объявлений методов
class EmptyMethodDeclarationList : public IMethodDeclarationList
{
public:
	EmptyMethodDeclarationList() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

//Интерфейс объявления метода
class IMethodDeclaration
{
public:

	const IArgumentList* argList;
	const IVarDeclarationList* varList;
	const IStatementList* stateList;
	const IExp* e;

	IMethodDeclaration(const IArgumentList* _argList, const IVarDeclarationList* _varList, const IStatementList* _stateList, const IExp* _e) :
		argList(_argList), varList(_varList), stateList(_stateList), e(_e) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma region ArgumentList

//Интерфейс списка аргументов
class IArgumentList
{
public:
	virtual string Accept(IVisitor *v) const = 0;
};

//Список аргументов с хвостом
class AddArgumentList : public IArgumentList
{

public:

	const IArgumentList* argList;

	AddArgumentList(const IArgumentList* _argList) :argList(_argList) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Один аргумент
class OnlyArgumentList : public IArgumentList
{
public:

	OnlyArgumentList() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Пустой список аргументов
class ZeroArgumentList : public IArgumentList {

public:

	ZeroArgumentList() {}

	string Accept(IVisitor *v) const
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
	virtual string Accept(IVisitor *v) const = 0;
};

//Список утверждений с одним утверждением и хвостом
class AddStatementList : public IStatementList
{
public:
	const IStatement* s;
	const IStatementList* stateList;

	AddStatementList(const IStatement* _s, const IStatementList* _stateList) : stateList(_stateList), s(_s) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Пустой список объявлений методов
class EmptyStatementList : public IStatementList
{
public:
	EmptyStatementList() {}

	string Accept(IVisitor *v) const
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
	virtual string Accept(IVisitor *v) const = 0;
};

//Составное утверждение
class CompoundStatement : public IStatement
{
public:
	const IStatementList* stateList;

	CompoundStatement(const IStatementList* _stateList) :stateList(_stateList) {}

	string Accept(IVisitor *v) const
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

	string Accept(IVisitor *v) const
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

	string Accept(IVisitor *v) const
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

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Инициализация
class AssignStatement :public IStatement
{
public:
	const IExp* e;

	AssignStatement(const IExp* _e) :e(_e) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Присваивание элемента массива
class AssignArrayElementStatement :public IStatement
{
public:
	const IExp* e;
	const IExp* index;


	AssignArrayElementStatement(const IExp* _index, const IExp* _e) :index(_index), e(_e) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

#pragma region ExpressionList

//Интерфейс списка утверждений
class IExpList {
public:
	virtual string Accept(IVisitor *v) const = 0;
};

//Список выражений с хвостом
class AddExpList : public IExpList {

public:

	const IExp* e1;
	const IExpList* eList;

	AddExpList(const IExp* _e1, const IExpList *_eList) :e1(_e1), eList(_eList) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Список выражений, состоящий из одного элемента
class OnlyExpList : public IExpList {

public:
	const IExp* e1;

	OnlyExpList(const IExp* _e1) :e1(_e1) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Пустой список выражений
class ZeroExpList : public IExpList {

public:

	ZeroExpList() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

#pragma endregion

#pragma region Expression

//Интерфейс выражения
class IExp {
public:
	virtual string Accept(IVisitor *v) const = 0;
};

//Бинарная операция
class BinopExp : public IExp {
public:

	const IExp *e1, *e2;

	BinopExp(const IExp *_e1, const IExp *_e2) :e1(_e1), e2(_e2) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Возвращение элемента массива
class GetArrayElementExp : public IExp {
public:

	const IExp *e1, *e2;

	GetArrayElementExp(const IExp *_e1, const IExp *_e2) :e1(_e1), e2(_e2) {}

	string Accept(IVisitor *v) const
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

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Вызвать метод
class MethodExp : public IExp
{
public:

	const IExp *e1;
	const IExpList *eList;

	MethodExp(const IExp *_e1, const IExpList* _eList) :e1(_e1), eList(_eList) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Числовое выражение
class NumExp : public IExp {
public:

	const int num;

	NumExp(const int _num) :num(_num) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Булево выражение
class BoolExp : public IExp {
public:

	const bool flag;

	BoolExp(const bool _flag) :flag(_flag) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Идентификатор
class IDExp : public IExp {
public:

	IDExp() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Указатель на активный элемент
class ThisExp : public IExp {
public:

	ThisExp() {}


	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Получение массива
class GetArrayExp : public IExp {
public:

	const IExp *e1;

	GetArrayExp(const IExp *_e1) :e1(_e1) {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

//Создание нового объекта
class NewObjectExp : public IExp
{
public:

	NewObjectExp() {}

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}

};

//Отрицание утверждения
class NegativeExp : public IExp {
public:

	const IExp *e1;

	NegativeExp(const IExp *_e1) : e1(_e1) {}

	string Accept(IVisitor *v) const
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

	string Accept(IVisitor *v) const
	{
		return v->visit(this);
	}
};

#pragma endregion

#pragma endregion

//Класс посетителя, который создаёт синтаксическое дерево
class Printer : public IVisitor
{
public:
	string visit(const Program* n)
	{
		fout = ofstream("graph.dot");
		fout << "digraph G" << endl << "{" << endl;
		string child1 = n->mClass->Accept(this);
		string child2 = n->classList->Accept(this);
		fout << "Program->" << child1 << endl << "Program->" << child2 << endl<<"}"<<endl;
		fout.close();
		return "";
	}

	string visit(const IMainClass* n)
	{
		string name = "MainClass";
		string child = n->statement->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const AddClassDeclarationList* n)
	{
		string name = CompoundString("ClassList", classListCount);
		classListCount++;
		string child1 = n->classList->Accept(this);
		string child2 = n->c->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const EmptyClassDeclarationList* n)
	{
		string name = CompoundString("EmptyClassList", classListCount);
		classListCount++;
		return name;
	}

	string visit(const IClassDeclaration* n)
	{
		string name = CompoundString("Class", classCount);
		classCount++;
		string child1 = n->methodList->Accept(this);
		string child2 = n->varList->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const AddVarDeclarationList* n)
	{
		string name = CompoundString("VarList", varListCount);
		varListCount++;
		string child1 = n->varList->Accept(this);
		string child2 = n->var->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const 	EmptyVarDeclarationList* n)
	{
		string name = CompoundString("EmptyVarList", varListCount);
		varListCount++;
		return name;
	}

	string visit(const IVarDeclaration* n)
	{
		string name = CompoundString("Var", varCount);
		varCount++;
		return name;
	}

	string visit(const AddMethodDeclarationList* n)
	{
		string name = CompoundString("MethodList", methodListCount);
		methodListCount++;
		string child1 = n->methodList->Accept(this);
		string child2 = n->m->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const EmptyMethodDeclarationList* n)
	{
		string name = CompoundString("EmptyMethodList", methodListCount);
		methodListCount++;
		return name;
	}

	string visit(const IMethodDeclaration* n)
	{
		string name = CompoundString("Method", methodCount);
		methodCount++;
		string argList = n->argList->Accept(this);
		string varList = n->varList->Accept(this);
		string stateList = n->stateList->Accept(this);
		string retExp = n->e->Accept(this);
		fout << name << "->" << argList << endl << name << "->" << varList << endl <<
			name << "->" << stateList << endl << name << "->" << retExp << " [label=\"return\"]" << endl;
		return name;
	}

	string visit(const AddArgumentList* n)
	{
		string name = CompoundString("ArgumentList", argumentListCount);
		argumentListCount++;
		string child = n->argList->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const OnlyArgumentList* n)
	{
		string name = CompoundString("Argument", argumentListCount);
		argumentListCount++;
		return name;
	}

	string visit(const ZeroArgumentList* n)
	{
		string name = CompoundString("EmptyArgumentList", argumentListCount);
		argumentListCount++;
		return name;
	}

	string visit(const AddStatementList* n)
	{
		string name = CompoundString("StatementList", statementListCount);
		statementListCount++;
		string child1 = n->stateList->Accept(this);
		string child2 = n->s->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const EmptyStatementList* n)
	{
		string name = CompoundString("EmptyStatementList", statementListCount);
		statementListCount++;
		return name;
	}

	string visit(const CompoundStatement* n)
	{
		string name = CompoundString("CompoundStatement", statementCount);
		statementCount++;
		string child = n->stateList->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const ConditionalStatement* n)
	{
		string name = CompoundString("ConditionalStatement", statementCount);
		statementCount++;
		string child1 = n->ifExp->Accept(this);
		string child2 = n->thenState->Accept(this);
		string child3 = n->elseState->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl << name << "->" << child3 << endl;
		return name;
	}

	string visit(const CycleStatement* n)
	{
		string name = CompoundString("CycleStatement", statementCount);
		statementCount++;
		string child1 = n->conditionExp->Accept(this);
		string child2 = n->actionState->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const PrintStatement* n)
	{
		string name = CompoundString("PrintStatement", statementCount);
		statementCount++;
		string child = n->e->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const AssignStatement* n)
	{
		string name = CompoundString("AssignStatement", statementCount);
		statementCount++;
		string child = n->e->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const AssignArrayElementStatement* n)
	{
		string name = CompoundString("AssignArrayElementStatement", statementCount);
		statementCount++;
		string child1 = n->e->Accept(this);
		string child2 = n->index->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const AddExpList* n)
	{
		string name = CompoundString("ExpressionList", expressionListCount);
		expressionListCount++;
		string child1 = n->eList->Accept(this);
		string child2 = n->e1->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const OnlyExpList* n)
	{
		string name = CompoundString("OneExpressionList", expressionListCount);
		expressionListCount++;
		string child = n->e1->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const ZeroExpList* n)
	{
		string name = CompoundString("EmptyExpressionList", expressionListCount);
		expressionListCount++;
		return name;
	}

	string visit(const BinopExp* n)
	{
		string name = CompoundString("BinopExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this);
		string child2 = n->e2->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const GetArrayElementExp* n)
	{
		string name = CompoundString("GetArElExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this);
		string child2 = n->e2->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const GetLengthExp* n)
	{
		string name = CompoundString("GetLenExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const MethodExp* n)
	{
		string name = CompoundString("MethodExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this);
		string child2 = n->eList->Accept(this);
		fout << name << "->" << child1 << endl << name << "->" << child2 << endl;
		return name;
	}

	string visit(const NumExp* n)
	{
		string name = CompoundString("NumExp", expressionCount);
		expressionCount++;
		return name;
	}

	string visit(const BoolExp* n)
	{
		string name = CompoundString("BoolExp", expressionCount);
		expressionCount++;
		return name;
	}

	string visit(const IDExp* n)
	{
		string name = CompoundString("IDExp", expressionCount);
		expressionCount++;
		return name;
	}

	string visit(const ThisExp* n)
	{
		string name = CompoundString("ThisExp", expressionCount);
		expressionCount++;
		return name;
	}

	string visit(const GetArrayExp* n)
	{
		string name = CompoundString("GetArExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const NewObjectExp* n)
	{
		string name = CompoundString("NewObjExp", expressionCount);
		expressionCount++;
		return name;
	}

	string visit(const NegativeExp* n)
	{
		string name = CompoundString("NegExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

	string visit(const EnclosedExp* n)
	{
		string name = CompoundString("EnclExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this);
		fout << name << "->" << child << endl;
		return name;
	}

private:
	string CompoundString(string arg1, int arg2)
	{
		ostringstream ost;
		ost << arg1 << arg2;
		return ost.str();
	}

	ofstream fout;

	int classCount = 0;
	int classListCount = 0;
	int methodCount = 0;
	int methodListCount = 0;
	int varCount = 0;
	int varListCount = 0;
	int argumentListCount = 0;
	int statementCount = 0;
	int statementListCount = 0;
	int expressionCount = 0;
	int expressionListCount = 0;

};
