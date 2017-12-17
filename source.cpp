#include <stdio.h>
#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Symbol.h"
#include "Access.h"
#include "Frame.h"

extern Symbol* getIntern(const std::string& src);
#include "Table.h"
#include "GrammarDeclarations.h"
#include "Visitor.h"
#include "GrammarDescriptions.h"
#include "VarTableCreator.h"
#include "Printer.h"
#include "TypeChecker.h"
#include "AR_Visitor.h"

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

int main( int argc, char* argv[] )
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
	fopen_s( &yyin, argv[1], "r");
	yyparse();
	fclose(yyin);
	p.visit(prog);
	rValue symbolTable=v.visit(prog);//получаем таблицу символов
	tChecker.SetSymbolTable(symbolTable.info);
	rValue typeCheckInfo = tChecker.visit(prog);
	if (tChecker.errorCount == 0)
	{
		ARCreator arCreator;
		rValue arInformation = arCreator.visit(prog);
	}
	system("pause");//Не сразу закрываем консоль
	return 0;
}