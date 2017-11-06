//Класс посетителя, который создаёт таблицы символов
class VarTableCreator : public IVisitor
{
public:

	rValue visit(const Program* n)
	{
		rValue r;
		depth = 0;
		fout = ofstream("TableOfSymbols.txt");
		fout << "Table of Symbols" << endl << "{" << endl<< endl;
		const Info* mClassTable = n->mClass->Accept(this).info;
		const Info* classesTables = n->classList->Accept(this).info;

		r.info = new ContainerInfo(mClassTable->GetNestedInfo());
		vector<const Info*> classesInfos = classesTables->GetNestedInfo();
		for (int i = 0; i < classesInfos.size(); i++)
			r.info->PushNestedInfo(classesInfos[i]);

		fout << "}" << endl;
		fout.close();
		return r;
	}

	rValue visit(const IMainClass* n)
	{
		depth++;
		MakeOffset();
		rValue table;
		table.info = new ClassInfo(new IType(getIntern("MainClass")), n->name, { new Info(new IType(getIntern("String")),n->argName,{}) });

		fout << "MainClass " << n->name->str << endl;
		MakeOffset();
		fout << "{" << endl;
		depth++;
		MakeOffset();
		fout << "String " << n->argName->str << endl;
		depth--;
		MakeOffset();
		fout << "}" << endl;
		depth--;
		fout << endl;

		return table;
	}

	rValue visit(const AddClassDeclarationList* n)
	{
		rValue table;

		const Info* classesListTable = n->classList->Accept(this).info;
		const Info* classTable = n->c->Accept(this).info;
		table.info = new ContainerInfo(classesListTable->GetNestedInfo());
		table.info->PushNestedInfo(classTable);

		return table;
	}

	rValue visit(const EmptyClassDeclarationList* n)
	{
		rValue table;

		table.info = new ContainerInfo({});

		return table;
	}

	rValue visit(const IClassDeclaration* n)
	{
		rValue table;
		depth ++;
		MakeOffset();
		fout << "Class " <<n->name->str<< endl;
		MakeOffset();
		fout << "{" << endl << endl;
		MakeOffset();
		fout << "Variables:"<<endl;
		const Info* varListTable = n->varList->Accept(this).info;
		fout << endl;
		MakeOffset();
		fout << "Methods:" << endl;
		const Info* methodListTables = n->methodList->Accept(this).info;
		MakeOffset();
		fout << "}" << endl<<endl;
		depth--;

		table.info = new ClassInfo(n->name, varListTable->GetNestedInfo());
		vector<const Info*> methodInfos = methodListTables->GetNestedInfo();
		for (int i = 0; i < methodInfos.size(); i++)
			table.info->PushNestedInfo(methodInfos[i]);
		return table;
	}

	rValue visit(const AddVarDeclarationList* n)
	{
		rValue table;

		const Info* varListTable = n->varList->Accept(this).info;
		const Info* varTable = n->var->Accept(this).info;
		table.info = new ContainerInfo( varListTable->GetNestedInfo());
		table.info->PushNestedInfo(varTable);

		return table;
	}

	rValue visit(const 	EmptyVarDeclarationList* n)
	{
		rValue table;

		table.info = new ContainerInfo({});

		return table;
	}

	rValue visit(const IVarDeclaration* n)
	{
		rValue table;
		depth++;
		MakeOffset();
		fout << n->typ->typeName->str <<" "<< n->name->str << endl;
		depth--;

		table.info = new VariableInfo(n->typ,n->name);
		return table;
	}

	rValue visit(const AddMethodDeclarationList* n)
	{
		rValue table;

		const Info* methodListTable = n->methodList->Accept(this).info;
		const Info* methodTable = n->m->Accept(this).info;
		table.info = new ContainerInfo(methodListTable->GetNestedInfo());
		table.info->PushNestedInfo(methodTable);

		return table;
	}

	rValue visit(const EmptyMethodDeclarationList* n)
	{
		rValue table;

		table.info = new ContainerInfo({});

		return table;
	}

	rValue visit(const IMethodDeclaration* n)
	{
		rValue table;
		depth++;
		MakeOffset();
		fout << n->typ->typeName->str<<" "<< n->name->str << endl;
		MakeOffset();
		fout << "{" << endl << endl;
		fout << endl;
		MakeOffset();
		fout << "Arguments:" << endl;
		const Info* argListTable = n->argList->Accept(this).info;
		fout << endl;
		MakeOffset();
		fout << "Variables:" << endl;
		const Info* varListTables = n->varList->Accept(this).info;
		MakeOffset();
		fout << "}" << endl << endl;
		depth--;

		table.info = new MethodInfo(n->typ,n->name, argListTable->GetNestedInfo());
		vector<const Info*> varInfos = varListTables->GetNestedInfo();
		for (int i = 0; i < varInfos.size(); i++)
			table.info->PushNestedInfo(varInfos[i]);
		return table;
	}

	rValue visit(const AddArgumentList* n)
	{
		rValue table;

		depth++;
		MakeOffset();
		fout << n->typ->typeName->str << " " << n->name->str << endl;
		depth--;

		const Info* argListTable = n->argList->Accept(this).info;
		table.info = new ContainerInfo({new VariableInfo(n->typ,n->name)});
		vector<const Info*> argInfos = argListTable->GetNestedInfo();
		for (int i = 0; i < argInfos.size(); i++)
			table.info->PushNestedInfo(argInfos[i]);

		return table;
	}

	rValue visit(const OnlyArgumentList* n)
	{
		rValue table;

		depth++;
		MakeOffset();
		fout << n->typ->typeName->str << " " << n->name->str << endl;
		depth--;

		table.info = new ContainerInfo({ new VariableInfo(n->typ,n->name) });
		return table;
	}

	rValue visit(const ZeroArgumentList* n)
	{
		rValue table;

		table.info = new ContainerInfo({});

		return table;
	}

	rValue visit(const AddStatementList* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const EmptyStatementList* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const CompoundStatement* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const ConditionalStatement* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const CycleStatement* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const PrintStatement* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const AssignStatement* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const AssignArrayElementStatement* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const AddExpList* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const OnlyExpList* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const ZeroExpList* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const BinopExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const GetArrayElementExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const GetLengthExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const MethodExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const NumExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const BoolExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const IDExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const ThisExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const GetArrayExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const NewObjectExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const NegativeExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const EnclosedExp* n)
	{
		rValue table;
		return table;
	}

private:
	/*
	string CompoundString(string arg1, int arg2)
	{
		ostringstream ost;
		ost << arg1 << arg2;
		return ost.str();
	}
	*/

	//Сделать отступ на depth
	void MakeOffset()
	{
		for (int i = 0; i < depth; i++)
			fout << "\t";
	}

	ofstream fout;
	int depth;//Глубина вложенности переменных


};
