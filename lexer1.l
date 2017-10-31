%option noyywrap

%{
#define YY_USER_ACTION action(yy_act, yyleng);

#include <stdio.h>
#include <iostream>
#include "parser.h"
using namespace std;

struct Location 
{
	int line, symbolBegin;
} location;

int wordsNum=0;
bool eofRead=false;

void action(int yyact, int yyleng)
{
	//if (yyact>24)
		//return;
	//cout<<"("<<location.line<<", "<<location.symbolBegin<<")";
	location.symbolBegin+=yyleng;
}

%}

%%

[0-9]+ {yylval.Int = atoi(yytext); return NUM;};

if return IFWORD;
else return ELSEWORD;
while return WHILEWORD;
true return TRUE;
false return FALSE;

class return CLASSWORD;
public return PUBLICWORD;
private return PRIVATEWORD;
static return STATICWORD;
main return MAINWORD;
extends return EXTENSIONWORD;
this return THISWORD;
length return LENGTHWORD;
new return NEWWORD;
void return VOIDWORD;
return return RETURNWORD;

System.out.println return PRINTWORD;

String return STRINGWORD;
int return INTWORD;
boolean return BOOLWORD;

[a-zA-Z][a-zA-Z0-9_]* return IDENTIFIER;

= return ASSIGN;
\+ return PLUS;
\- return MINUS;
\* return MULTIPLY;
% return MOD;
\< return LESS;
\> return GREATER;
== return EQUAL;
! return NOT;
&& return AND;
\|\| return OR;

\( return OBRACE;
\) return EBRACE;
\{ return FOBRACE;
\} return FEBRACE;
\[ return SQOBRACE;
\] return SQEBRACE;
\. return DOT;
\, return COMMA;
\$ return EOFL;
\/\/[^\n]* /*игнорируем пробелы и знаки табуляции*/;
\; return SEMICOLON;
\n {location.line++; location.symbolBegin=0; printf("\n");}
[ \t]+ /*игнорируем пробелы и знаки табуляции*/;
<<eof>> {if (!eofRead) {eofRead=true; return EOFL;} else yyterminate();}

%%