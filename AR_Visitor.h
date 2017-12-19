
#include "X86MiniJavaFrame.h"

//Класс посетителя, который создаёт записи активации
class ARCreator : public IVisitor
{

public:

	rValue visit(const Program* n)
	{
		rValue r;
		//fout = ofstream("Stack.txt");
		//fout << "Hi" << endl << endl;
		const Info* mClassTable = n->mClass->Accept(this).info;

		r.info = new ContainerInfo({ mClassTable });
		for (auto classDecl : n->classes)
			r.info->PushNestedInfo(classDecl->Accept(this).info);

		//fout.close();
		return r;
	}

	rValue visit(const IMainClass* n)
	{
		rValue table;
		table.info = new ClassInfo(new IType(getIntern("MainClass")), n->name, { new Info(new IType(getIntern("String")),n->argName,{}) });

		const Info* statementInfo = n->statement->Accept(this).info;

		return table;
	}

	rValue visit(const IClassDeclaration* n)
	{
		rValue table;
		table.info = new ClassInfo(n->name, {});

		for (auto method : n->methods)
			table.info->PushNestedInfo(method->Accept(this).info);

		return table;
	}

	rValue visit(const IVarDeclaration* n)
	{
		rValue table;
		return table;
	}

	rValue visit(const IMethodDeclaration* n)
	{
		rValue table;

		X86MiniJavaFrame* ex=new X86MiniJavaFrame();
		
		for (auto arg : n->args)
			ex->AddFormal(arg->typ,arg->name);
		for (auto var : n->vars)
			ex->AddLocal(var->typ, var->name);

		table.info = new FrameInfo(n->name,ex);

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
		n->conditionExp->Accept(this);
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
		//fout << "Hello" << endl;
		//fout << n->methodName->str << endl;
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

};
