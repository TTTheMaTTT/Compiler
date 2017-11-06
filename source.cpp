#include <stdio.h>
#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Symbol.h"
extern Symbol* getIntern(const string& src);
#include "Table.h"
#include "GrammarDeclarations.h"
#include "Visitor.h"
#include "GrammarDescriptions.h"
#include "VarTableCreator.h"

using namespace std;

extern const Program* prog;
extern VarTableCreator v;

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

int main()
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
	yyin = fopen("file.txt", "r");
	yyparse();
	fclose(yyin);
	system("pause");//Не сразу закрываем консоль
	rValue information=v.visit(prog);
	return 0;
}