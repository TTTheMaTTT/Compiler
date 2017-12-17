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
		fout << "Program ->" << child1 << endl;
		for (auto classDecl : n->classes)
		{
			string child2 = classDecl->Accept(this).sValue;
			fout << "Program->" << child2 << endl;
		}
		fout << "}" << endl;
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

	rValue visit(const IClassDeclaration* n)
	{
		rValue name;
		name.sValue = CompoundString("Class", classCount);
		classCount++;
		for (auto var : n->vars)
		{
			string child = var->Accept(this).sValue;
			fout << name.sValue << "->" << child << endl;
		}
		for (auto method : n->methods)
		{
			string child = method->Accept(this).sValue;
			fout << name.sValue << "->" << child << endl;
		}
		return name;
	}

	rValue visit(const IVarDeclaration* n)
	{
		rValue name;
		name.sValue = CompoundString("Var", varCount);
		varCount++;
		return name;
	}
	
	rValue visit(const IMethodDeclaration* n)
	{
		rValue name;
		name.sValue = CompoundString("Method", methodCount);
		methodCount++;
		string retExp = n->e->Accept(this).sValue;

		for (auto arg : n->args)
		{
			string child = arg->Accept(this).sValue;
			fout << name.sValue << "->" << child << endl;
		}
		for (auto var : n->vars)
		{
			string child = var->Accept(this).sValue;
			fout << name.sValue << "->" << child << endl;
		}
		for (auto state : n->statements)
		{
			string child = state->Accept(this).sValue;
			fout << name.sValue << "->" << child << endl;
		}
		fout << name.sValue << "->" << retExp<<" [label=\"return\"]" << endl;

		return name;
	}


	rValue visit(const CompoundStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("CompoundStatement", statementCount);
		statementCount++;
		for (auto state : n->statements)
		{
			string child = state->Accept(this).sValue;
			fout << name.sValue << "->" << child << endl;
		}
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
		fout << name.sValue << "->" << child1 << endl 
			<< name.sValue << "->" << child2 << endl << name.sValue << "->" << child3 << endl;
		return name;
	}

	rValue visit(const CycleStatement* n)
	{
		rValue name;
		name.sValue = CompoundString("CycleStatement", statementCount) ;
		statementCount++;
		string child1 = n->conditionExp->Accept(this).sValue;
		string child2 = n->actionState->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2<< endl;
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

	rValue visit(const TernExp* n)
	{
		rValue name;
		name.sValue = CompoundString("TernExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this).sValue;
		string child2 = n->e2->Accept(this).sValue;
		string child3 = n->e3->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl<< 
				name.sValue << "->" << child3 << endl;
		return name;
	}

	rValue visit(const GetArrayElementExp* n)
	{
		rValue name;
		name.sValue =  CompoundString("GetArElExp", expressionCount);
		expressionCount++;
		string child1 = n->e1->Accept(this).sValue;
		string child2 = n->e2->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl << name.sValue << "->" << child2 << endl;
		return name;
	}

	rValue visit(const GetLengthExp* n)
	{
		rValue name;
		name.sValue =  CompoundString("GetLenExp", expressionCount);
		expressionCount++;
		string child = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child<< endl;
		return name;
	}

	rValue visit(const MethodExp* n)
	{
		rValue name;
		name.sValue = CompoundString("MethodExp", expressionCount) ;
		expressionCount++;
		string child1 = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child1 << endl;
		for (auto exp : n->args)
		{
			string child = exp->Accept(this).sValue;
			fout << name.sValue << "->" << child << " [label=\"method exp\"]" << endl;
		}
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
		name.sValue = CompoundString("BoolExp", expressionCount) ;
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
		name.sValue = CompoundString("NegExp", expressionCount) ;
		expressionCount++;
		string child = n->e1->Accept(this).sValue;
		fout << name.sValue << "->" << child << endl;
		return name;
	}

	rValue visit(const EnclosedExp* n)
	{
		rValue name;
		name.sValue = CompoundString("EnclExp", expressionCount) ;
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
	int methodCount = 0;
	int varCount = 0;
	int statementCount = 0;
	int expressionCount = 0;

};
