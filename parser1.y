%defines "parser.h"

%code requires 
{
#include "GrammarDeclarations.h"
#include "Symbol.h"
}

%{
/*
ToDo: позаботиться о нормальном выделении и освобождении памяти
	  Позаботаться о разных типах синтаксических ошибок (сейчас учитываются ошибки только в StatementList)
	  Сделать нормальную локацию ошибок
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Symbol.h"
extern Symbol* getIntern(const std::string& src);
#include "Table.h"
#include "GrammarDeclarations.h"
#include "Visitor.h"
#include "GrammarDescriptions.h"

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

const Program* prog;

static int prevErrorLine=0;

%}

%locations

%union {
	int Int;
	const Symbol* Symbol;//Символ
	const IType* Type;//Тип объектов
	const Extension* Extension;//Тип, указывающий информацию о наследовании
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
%token PLUS MINUS MULTIPLY MOD
%token SEMICOLON COMMA DOT
%token NOT OR AND LESS GREATER EQUAL IFWORD ELSEWORD WHILEWORD
%token ASSIGN
%token EOFL STRINGWORD BOOLWORD INTWORD CLASSWORD NEWWORD THISWORD PUBLICWORD PRIVATEWORD STATICWORD VOIDWORD RETURNWORD MAINWORD 
%token EXTENSIONWORD PRINTWORD LENGTHWORD TRUE FALSE
%token <Symbol> IDENTIFIER 
%token <Int> NUM

//Операции с приоритетами
%nonassoc AND
%nonassoc OR
%nonassoc LESS GREATER EQUAL
%left PLUS MINUS
%left MULTIPLY MOD
%right NOT
%left DOT SQOBRACE

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
%type <Extension> Extension

%%

Goal:
	MainClass ClassDeclarationList EOFL {prog=$$=new Program($1,$2); 	printf("Всё хорошо\n");}
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
	{$$=new IClassDeclaration($2,$3,$5,$6,yylloc.first_line);}
	;

Extension:
	EXTENSIONWORD IDENTIFIER {$$=new Extension($2,yylloc.first_line);}
	|
	{$$=new Extension();}
	;

VarDeclarationList:
	VarDeclarationList VarDeclaration {$$=new AddVarDeclarationList($1,$2);}
	|
	{$$=new EmptyVarDeclarationList();}
	;	

VarDeclaration:
	Type IDENTIFIER SEMICOLON {$$=new IVarDeclaration($1,$2,yylloc.first_line);}
	;

MethodDeclarationList:
	MethodDeclarationList MethodDeclaration {$$=new AddMethodDeclarationList($1,$2);}
	|
	{$$=new EmptyMethodDeclarationList();}
	;

MethodDeclaration:
	ScopeAttribute Type IDENTIFIER OBRACE ArgumentList EBRACE
		FOBRACE VarDeclarationList StatementList RETURNWORD Expression SEMICOLON FEBRACE 
	{$$=new IMethodDeclaration($2,$3,$5,$8,$9,$11,yylloc.first_line);}
	;

ScopeAttribute:
	PUBLICWORD
	|
	PRIVATEWORD
	;

ArgumentList:
	Type IDENTIFIER COMMA ArgumentList {$$=new AddArgumentList($1,$2,$4,yylloc.first_line);}
	|
	Type IDENTIFIER {$$=new OnlyArgumentList($1,$2,yylloc.first_line);}
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
	|
	Err SEMICOLON StatementList{$$=new ErrorStatementList($3);
								//yyerror("Syntax Error");
								}
	;

Statement:
	FOBRACE StatementList FEBRACE {$$=new CompoundStatement($2,yylloc.first_line);}
	|
	IFWORD OBRACE Expression EBRACE Statement ELSEWORD Statement {$$=new ConditionalStatement($3,$5,$7,yylloc.first_line);}
	|
	WHILEWORD OBRACE Expression EBRACE Statement {$$=new CycleStatement($3,$5,yylloc.first_line);}
	|
	PRINTWORD OBRACE Expression EBRACE SEMICOLON {$$=new PrintStatement($3,yylloc.first_line);}
	|
	IDENTIFIER ASSIGN Expression SEMICOLON {$$=new AssignStatement($1,$3,yylloc.first_line);}
	|
	IDENTIFIER SQOBRACE Expression SQEBRACE ASSIGN Expression SEMICOLON {$$=new AssignArrayElementStatement($1,$3,$6,yylloc.first_line);}
	;

ExpressionList:
	Expression COMMA ExpressionList {$$=new AddExpList($1,$3);}
	|
	Expression {$$=new OnlyExpList($1);}
	|
	{$$=new ZeroExpList();}
	;

Expression:
	Expression PLUS Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::PLUS);}
	|
	Expression MINUS Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::MINUS);}
	|
	Expression MULTIPLY Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::MULTIPLY);}
	|
	Expression MOD Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::MOD);}
	|
	Expression AND Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::AND);}
	|
	Expression OR Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::OR);}
	|
	Expression LESS Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::LESS);}
	|
	Expression GREATER Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::GREATER);}
	|
	Expression EQUAL Expression {$$=new BinopExp($1,$3,yylloc.first_line,binOpType::EQUAL);}
	|
	Expression SQOBRACE Expression SQEBRACE {$$=new GetArrayElementExp($1,$3,yylloc.first_line);}
	|
	Expression DOT LENGTHWORD {$$=new GetLengthExp($1,yylloc.first_line);}
	|
	Expression DOT IDENTIFIER OBRACE ExpressionList EBRACE {$$=new MethodExp($1,$3,$5,yylloc.first_line);}
	|
	NUM {$$=new NumExp($1,yylloc.first_line);}
	|
	TRUE {$$=new BoolExp(true,yylloc.first_line);}
	|
	FALSE {$$=new BoolExp(false,yylloc.first_line);}
	|
	IDENTIFIER {$$=new IDExp($1,yylloc.first_line);}
	|
	THISWORD {$$=new ThisExp();}
	|
	NEWWORD INTWORD SQOBRACE Expression SQEBRACE {$$=new GetArrayExp($4,yylloc.first_line);}
	|
	NEWWORD IDENTIFIER OBRACE EBRACE {$$=new NewObjectExp($2,yylloc.first_line);}
	|
	OBRACE Expression EBRACE {$$=new EnclosedExp($2,yylloc.first_line);}
	|
	NOT Expression {$$=new NegativeExp($2,yylloc.first_line);}
	;

Err:
	error {yyerror("Syntax Error");};

%%

// we have to code this function
void yyerror(const char* msg)
{
	if (prevErrorLine!=yylloc.first_line)
	{
		fprintf(stderr, "ошибка: [%d,%d] - %s\n",yylloc.first_line, yylloc.first_column, msg);
		prevErrorLine=yylloc.first_line;
	}
	//system("pause");//Не сразу закрываем консоль
}