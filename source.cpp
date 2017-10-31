#include <stdio.h>
#include <string.h>
#include <iostream>
#include "parser.h"

#include "GrammarDescriptions.h"

using namespace std;

Program prog;
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

int main()
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
	yyin = fopen("file.txt", "r");
	yyparse();
	fclose(yyin);
	system("pause");//Не сразу закрываем консоль
	p.visit(&prog);
	return 0;
}

// we have to code this function
void yyerror(const char* msg)
{
	fprintf(stderr, "ошибка: %s\n", str);
	system("pause");//Не сразу закрываем консоль
}