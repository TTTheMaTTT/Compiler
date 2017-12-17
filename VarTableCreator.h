//Класс посетителя, который создаёт таблицы символов
class VarTableCreator : public IVisitor
{
public:

	rValue visit(const Program* n)
	{
		rValue r;
		depth = 0;
		fout = ofstream("TableOfSymbols.txt");
		fout << "Table of Symbols" << endl << "{" << endl << endl;
		const Info* mClassTable = n->mClass->Accept(this).info;

		r.info = new ContainerInfo({mClassTable});
		for (auto classDecl: n->classes)
			r.info->PushNestedInfo(classDecl->Accept(this).info);

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

	rValue visit(const IClassDeclaration* n)
	{
		rValue table;
		
		table.info = new ClassInfo(n->name, {});
		
		depth ++;
		MakeOffset();
		fout << "Class " <<n->name->str<< endl;
		MakeOffset();
		fout << "{" << endl << endl;
		MakeOffset();

		fout << "Variables:"<<endl;
		for (auto var : n->vars)
			table.info->PushNestedInfo(var->Accept(this).info);
		fout << endl;
		MakeOffset();

		fout << "Methods:" << endl;
		for (auto method : n->methods)
			table.info->PushNestedInfo(method->Accept(this).info);
		MakeOffset();
		fout << "}" << endl<<endl;
		depth--;

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

	rValue visit(const IMethodDeclaration* n)
	{
		rValue table;
		table.info = new MethodInfo(n->typ, n->name, {});

		depth++;
		MakeOffset();
		fout << n->typ->typeName->str<<" "<< n->name->str << endl;
		MakeOffset();
		fout << "{" << endl << endl;
		fout << endl;
		MakeOffset();

		fout << "Arguments:" << endl;
		for (auto arg : n->args)
		{
			Info* argInfo = arg->Accept(this).info;
			argInfo->SetInfoType("arg");
			table.info->PushNestedInfo(argInfo);
		}
		fout << endl;
		MakeOffset();

		fout << "Variables:" << endl;
		for (auto var : n->vars)
			table.info->PushNestedInfo(var->Accept(this).info);
		MakeOffset();
		fout << "}" << endl << endl;
		depth--;

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

	rValue visit(const BinopExp* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const TernExp* n)
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
