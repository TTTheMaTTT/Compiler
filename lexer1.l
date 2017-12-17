%option noyywrap

%{
#define YY_USER_ACTION action(yy_act, yyleng);

#include <stdio.h>
#include <iostream>
#include "parser.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#include "Symbol.h"
#include "Table.h"

struct Location 
{
	int line, symbolBegin;
} location;

int wordsNum=0;
bool eofRead=false;

//»нтернирование строк в указатели на объект класса Symbol
Symbol* getIntern(const string& src)
{
	static unordered_map<string, Symbol*> allStrings;
	auto cached = allStrings.find(src);
	if (cached != allStrings.end()) {
		return cached->second;
	}
	Symbol* newVal = new Symbol(src);
	allStrings.insert({ src, newVal });
	return newVal;
}

void action(int yyact, int yyleng)
{
	//if (yyact>24)
		//return;
	//cout<<"("<<location.line<<", "<<location.symbolBegin<<")";
	yylloc.first_line = location.line;
	yylloc.first_column = location.symbolBegin;
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
short return SHORTWORD;
boolean return BOOLWORD;

[a-zA-Z][a-zA-Z0-9_]* {yylval.Symbol=getIntern(yytext) ; return IDENTIFIER;};

= return ASSIGN;
\+ return PLUS;
\- return MINUS;
\* return MULTIPLY;
\: return COLON;
\? return INTERROGATION;
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
\/\/[^\n]* /*игнорируем пробелы и знаки табул€ции*/;
\; return SEMICOLON;
\n {location.line++; location.symbolBegin=0;}
[ \t]+ /*игнорируем пробелы и знаки табул€ции*/;
<<eof>> {if (!eofRead) {eofRead=true; return EOFL;} else yyterminate();}

%%