%defines "parser.h"

%code requires 
{
#include "GrammarDeclarations.h"
#include "Symbol.h"
}

%{
/*
ToDo: позаботиться о нормальном выделении и освобождении памяти

*/
#include <stdio.h>
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

// this function will be generated
// by flex
extern int yylex(); // lexical analyzer
	 
// we have to code this function
extern void yyerror(const char*);

extern FILE * yyin;

// this function is called syntax parser
// just the parser, the parse
extern int yyparse();

VarTableCreator v;
const Program* prog;

%}

%locations

%union {
	int Int;
	const Symbol* Symbol;//Символ
	const IType* Type;//Тип объектов
	const Program* Program;
	const IMainClass* MainClass;
	const IClassDeclarationList* ClassDeclarationList;
	const IClassDeclaration* ClassDeclaration;
	const IVarDeclarationList* VarDeclarationList;
	const IVarDeclaration* VarDeclaration;
	const IMethodDeclarationList* MethodDeclarationList;
	const IMethodDeclaration* MethodDeclaration;
	const IArgumentList* ArgumentList;
	const IStatementList* StatementList;
	const IStatement* Statement;
	const IExpList* ExpList;
	const IExp* Exp;
}

%token FOBRACE FEBRACE SQOBRACE SQEBRACE OBRACE EBRACE
%token SEMICOLON COMMA DOT
%token OR AND NOT EQUAL GREATER LESS IFWORD ELSEWORD WHILEWORD
%token MOD MULTIPLY MINUS PLUS ASSIGN
%token EOFL STRINGWORD BOOLWORD INTWORD CLASSWORD NEWWORD THISWORD PUBLICWORD PRIVATEWORD STATICWORD VOIDWORD RETURNWORD MAINWORD 
%token EXTENSIONWORD PRINTWORD LENGTHWORD TRUE FALSE
%token <Symbol> IDENTIFIER 
%token <Int> NUM

%type <Program> Goal
%type <MainClass> MainClass
%type <ClassDeclarationList> ClassDeclarationList
%type <ClassDeclaration> ClassDeclaration
%type <VarDeclarationList> VarDeclarationList
%type <VarDeclaration> VarDeclaration
%type <MethodDeclarationList> MethodDeclarationList
%type <MethodDeclaration> MethodDeclaration
%type <ArgumentList> ArgumentList
%type <StatementList> StatementList
%type <Statement> Statement
%type <ExpList> ExpressionList
%type <Exp> Expression
%type <Type> Type

%%

Goal:
	MainClass ClassDeclarationList EOFL {prog=$$=new Program($1,$2);}
	;

ClassDeclarationList:
	ClassDeclarationList ClassDeclaration {$$=new AddClassDeclarationList($1,$2);}
	|
	{$$=new EmptyClassDeclarationList();}
	;

MainClass:
	CLASSWORD IDENTIFIER FOBRACE 
		PUBLICWORD STATICWORD VOIDWORD MAINWORD OBRACE STRINGWORD SQOBRACE SQEBRACE IDENTIFIER EBRACE FOBRACE 
			Statement FEBRACE FEBRACE {$$=new IMainClass($2,$12,$15);}
	;

ClassDeclaration:
	CLASSWORD IDENTIFIER Extension FOBRACE VarDeclarationList MethodDeclarationList FEBRACE 
	{$$=new IClassDeclaration($2,$5,$6);}
	;

Extension:
	EXTENSIONWORD IDENTIFIER
	|
	;

VarDeclarationList:
	VarDeclarationList VarDeclaration {$$=new AddVarDeclarationList($1,$2);}
	|
	{$$=new EmptyVarDeclarationList();}
	;	

VarDeclaration:
	Type IDENTIFIER SEMICOLON {$$=new IVarDeclaration($1,$2);}
	;

MethodDeclarationList:
	MethodDeclarationList MethodDeclaration {$$=new AddMethodDeclarationList($1,$2);}
	|
	{$$=new EmptyMethodDeclarationList();}
	;

MethodDeclaration:
	ScopeAttribute Type IDENTIFIER OBRACE ArgumentList EBRACE
		FOBRACE VarDeclarationList StatementList RETURNWORD Expression SEMICOLON FEBRACE 
	{$$=new IMethodDeclaration($2,$3,$5,$8,$9,$11);}
	;

ScopeAttribute:
	PUBLICWORD
	|
	PRIVATEWORD
	;

ArgumentList:
	Type IDENTIFIER COMMA ArgumentList {$$=new AddArgumentList($1,$2,$4);}
	|
	Type IDENTIFIER {$$=new OnlyArgumentList($1,$2);}
	|
	{$$=new ZeroArgumentList();}
	;

Type:
	INTWORD SQOBRACE SQEBRACE {$$=new IType(getIntern("array of int"));}
	|
	BOOLWORD {$$=new IType(getIntern("bool"));}
	|
	INTWORD {$$=new IType(getIntern("int"));}
	|
	IDENTIFIER {$$=new IType($1);}
	;

StatementList:
	Statement StatementList {$$=new AddStatementList($1,$2);}
	|
	{$$=new EmptyStatementList();}
	;

Statement:
	FOBRACE StatementList FEBRACE {$$=new CompoundStatement($2);}
	|
	IFWORD OBRACE Expression EBRACE Statement ELSEWORD Statement {$$=new ConditionalStatement($3,$5,$7);}
	|
	WHILEWORD OBRACE Expression EBRACE Statement {$$=new CycleStatement($3,$5);}
	|
	PRINTWORD OBRACE Expression EBRACE SEMICOLON {$$=new PrintStatement($3);}
	|
	IDENTIFIER ASSIGN Expression SEMICOLON {$$=new AssignStatement($1,$3);}
	|
	IDENTIFIER SQOBRACE Expression SQEBRACE ASSIGN Expression SEMICOLON {$$=new AssignArrayElementStatement($1,$3,$6);}
	;

ExpressionList:
	Expression COMMA ExpressionList {$$=new AddExpList($1,$3);}
	|
	Expression {$$=new OnlyExpList($1);}
	|
	{$$=new ZeroExpList();}
	;

Expression:
	Expression BinOp Expression {$$=new BinopExp($1,$3);}
	|
	Expression SQOBRACE Expression SQEBRACE {$$=new GetArrayElementExp($1,$3);}
	|
	Expression DOT LENGTHWORD {$$=new GetLengthExp($1);}
	|
	Expression DOT IDENTIFIER OBRACE ExpressionList EBRACE {$$=new MethodExp($1,$3,$5);}
	|
	NUM {$$=new NumExp($1);}
	|
	TRUE {$$=new BoolExp(true);}
	|
	FALSE {$$=new BoolExp(false);}
	|
	IDENTIFIER {$$=new IDExp($1);}
	|
	THISWORD {$$=new ThisExp();}
	|
	NEWWORD INTWORD SQOBRACE Expression SQEBRACE {$$=new GetArrayExp($4);}
	|
	NEWWORD IDENTIFIER OBRACE EBRACE {$$=new NewObjectExp($2);}
	|
	NOT Expression {$$=new NegativeExp($2);}
	|
	OBRACE Expression EBRACE {$$=new EnclosedExp($2);}
	;

BinOp:
	AND
	| 
	LESS
	| 
	GREATER
	| 
	PLUS
	| 
	MINUS
	| 
	MULTIPLY
	| 
	MOD
	| 
	OR
	;

%%

// we have to code this function
void yyerror(const char* msg)
{
	fprintf(stderr, "ошибка: [%d,%d] - %s\n",yylloc.first_line, yylloc.first_column, msg);
	system("pause");//Не сразу закрываем консоль
}