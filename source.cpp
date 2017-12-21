#include <stdio.h>
#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Symbol.h"
#include "IRTree.h"
#include "Access.h"
#include "Frame.h"
#include "DefineChanger.h"

extern Symbol* getIntern(const std::string& src);
#include "Table.h"
#include "GrammarDeclarations.h"
#include "Visitor.h"
#include "GrammarDescriptions.h"
#include "VarTableCreator.h"
#include "Printer.h"
#include "TypeChecker.h"
#include "AR_Visitor.h"

#include "IRTranslate.h"

using namespace std;

extern const Program* prog;
VarTableCreator v;
TypeChecker tChecker;

Printer p;

// this function is called syntax parser
// just the parser, the parse
extern int yyparse();

extern FILE * yyin;

int yywrap()
{
	/*
	yyin=fopen("file.txt", "r");
	return 0;
	fclose(yyin);
	*/
	return 1;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
	char* filename1 = "1.txt";
	char* filename2 = "BinarySearch.txt";
	changeDefine(filename2, filename1);
	fopen_s(&yyin, filename1, "r");
	yyparse();
	fclose(yyin);
	p.visit(prog);
	rValue symbolTable = v.visit(prog);//получаем таблицу символов
	tChecker.SetSymbolTable(symbolTable.info);
	rValue typeCheckInfo = tChecker.visit(prog);
	if (tChecker.errorCount == 0)
	{
		ARCreator arCreator;
		rValue arInformation = arCreator.visit(prog);

		IRTranslator translator;
		translator.SetClassHierarchy(tChecker.GetClassHierarchy());
		translator.SetFrameTable(arInformation.info);
		translator.SetSymbolTable(symbolTable.info);
		rValue irTranslateInformation = translator.visit(prog);

	}
	system("pause");//Не сразу закрываем консоль
	return 0;
}