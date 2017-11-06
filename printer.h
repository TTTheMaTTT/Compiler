//Класс посетителя, который создаёт синтаксическое дерево
class Printer : public IVisitor
{
public:
	rValue visit(const Program* n)
	{
		rValue r;
		fout = ofstream("graph.dot");
		fout << "digraph G" << endl << "{" << endl;
		string child1 = n->mClass->Accept(this).sValue;
		string child2 = n->classList->Accept(this).sValue;
		fout << "Program->" << child1 << endl << "Program->" << child2 << endl<<"}"<<endl;
		fout.close();
		return r;
	}

	rValue visit(const IMainClass* n)
	{
		rValue name;
		name.sValue = "MainClass";
		string child = n->statement->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const AddClassDeclarationList* n)
	{
		rValue name;
		name.sValue = CompoundString("ClassList", classListCount);
		classListCount++;
		string child1 = n->classList->Accept(this).sValue;
		string child2 = n->c->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const EmptyClassDeclarationList* n)
	{
		rValue name;
		name.sValue = CompoundString("EmptyClassList", classListCount);
		classListCount++;
		return name;
	}

	rValue visit(const IClassDeclaration* n)
	{
		rValue name;
		name.sValue = CompoundString("Class", classCount);
		classCount++;
		string child1 = n->methodList->Accept(this).sValue;
		string child2 = n->varList->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const AddVarDeclarationList* n)
	{
		rValue name;
		name.sValue = CompoundString("VarList", varListCount);
		varListCount++;
		string child1 = n->varList->Accept(this).sValue;
		string child2 = n->var->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const 	EmptyVarDeclarationList* n)
	{
		rValue name;
		name.sValue = CompoundString("EmptyVarList", varListCount);
		varListCount++;
		return name;
	}

	rValue visit(const IVarDeclaration* n)
	{
		rValue name;
		name.sValue = CompoundString("Var", varCount);
		varCount++;
		return name;
	}

	rValue visit(const AddMethodDeclarationList* n)
	{
		rValue name;
		name.sValue = CompoundString("MethodList", methodListCount);
		methodListCount++;
		string child1 = n->methodList->Accept(this).sValue;
		string child2 = n->m->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const EmptyMethodDeclarationList* n)
	{
		rValue name;
		name.sValue = CompoundString("EmptyMethodList", methodListCount);
		methodListCount++;
		return name;
	}

	rValue visit(const IMethodDeclaration* n)
	{
		rValue name;
		name.sValue = CompoundString("Method", methodCount);
		methodCount++;
		string argList = n->argList->Accept(this).sValue;
		string varList = n->varList->Accept(this).sValue;
		string stateList = n->stateList->Accept(this).sValue;
		string retExp = n->e->Accept(this).sValue;
		fout << name.sValue << "->" << argList << endl << name.sValue << "->" << varList << endl <<
			name.sValue << "->" << stateList << endl << name.sValue << "->" << retExp << " [label=\"return\"]" << endl;
		return name;
	}

	rValue visit(const AddArgumentList* n)
	{
		rValue name;
		name.sValue = CompoundString("ArgumentList", argumentListCount);
		argumentListCount++;
		string child = n->argList->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const OnlyArgumentList* n)
	{
		rValue name;
		name.sValue = CompoundString("Argument", argumentListCount);
		argumentListCount++;
		return name;
	}

	rValue visit(const ZeroArgumentList* n)
	{
		rValue name;
		name.sValue = CompoundString("EmptyArgumentList", argumentListCount);
		argumentListCount++;
		return name;
	}

	rValue visit(const AddStatementList* n)
	{
		rValue name;
		name.sValue = CompoundString("StatementList", statementListCount);
		statementListCount++;
		string child1 = n->stateList->Accept(this).sValue;
		string child2 = n->s->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const EmptyStatementList* n)
	{
		rValue name;
		name.sValue = CompoundString("EmptyStatementList", statementListCount);
		statementListCount++;
		return name;
	}

	rValue visit(const CompoundStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("CompoundStatement", statementCount);
		statementCount++;
		string child = n->stateList->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const ConditionalStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("ConditionalStatement", statementCount);
		statementCount++;
		string child1 = n->ifExp->Accept(this).sValue;
		string child2 = n->thenState->Accept(this).sValue;
		string child3 = n->elseState->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl << name.sValue << "->" << child3 << endl;
		return name;
	}

	rValue visit(const CycleStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("CycleStatement", statementCount);
		statementCount++;
		string child1 = n->conditionExp->Accept(this).sValue;
		string child2 = n->actionState->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const PrintStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("PrintStatement", statementCount);
		statementCount++;
		string child = n->e->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const AssignStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("AssignStatement", statementCount);
		statementCount++;
		string child = n->e->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const AssignArrayElementStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("AssignArrayElementStatement", statementCount);
		statementCount++;
		string child1 = n->e->Accept(this).sValue;
		string child2 = n->index->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const AddExpList* n)
	{
		rValue name;
		name.sValue = CompoundString("ExpressionList", expressionListCount);
		expressionListCount++;
		string child1 = n->eList->Accept(this).sValue;
		string child2 = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const OnlyExpList* n)
	{
		rValue name;
		name.sValue = CompoundString("OneExpressionList", expressionListCount);
		expressionListCount++;
		string child = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const ZeroExpList* n)
	{
		rValue name;
		name.sValue = CompoundString("EmptyExpressionList", expressionListCount);
		expressionListCount++;
		return name;
	}

	rValue visit(const BinopExp* n)
	{
		rValue name;
		name.sValue = CompoundString("BinopExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this).sValue;
		string child2 = n->e2->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const GetArrayElementExp* n)
	{
		rValue name;
		name.sValue = CompoundString("GetArElExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this).sValue;
		string child2 = n->e2->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const GetLengthExp* n)
	{
		rValue name;
		name.sValue = CompoundString("GetLenExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const MethodExp* n)
	{
		rValue name;
		name.sValue = CompoundString("MethodExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this).sValue;
		string child2 = n->eList->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const NumExp* n)
	{
		rValue name;
		name.sValue = CompoundString("NumExp", expressionCount);
		expressionCount++;
		return name;
	}

	rValue visit(const BoolExp* n)
	{
		rValue name;
		name.sValue = CompoundString("BoolExp", expressionCount);
		expressionCount++;
		return name;
	}

	rValue visit(const IDExp* n)
	{
		rValue name;
		name.sValue = CompoundString("IDExp", expressionCount);
		expressionCount++;
		return name;
	}

	rValue visit(const ThisExp* n)
	{
		rValue name;
		name.sValue = CompoundString("ThisExp", expressionCount);
		expressionCount++;
		return name;
	}

	rValue visit(const GetArrayExp* n)
	{
		rValue name;
		name.sValue = CompoundString("GetArExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const NewObjectExp* n)
	{
		rValue name;
		name.sValue = CompoundString("NewObjExp", expressionCount);
		expressionCount++;
		return name;
	}

	rValue visit(const NegativeExp* n)
	{
		rValue name;
		name.sValue = CompoundString("NegExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const EnclosedExp* n)
	{
		rValue name;
		name.sValue = CompoundString("EnclExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
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
