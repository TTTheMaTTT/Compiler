/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 4 "parser1.y" /* yacc.c:1909  */

#include "GrammarDeclarations.h"
#include "Symbol.h"

#line 49 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FOBRACE = 258,
    FEBRACE = 259,
    SQOBRACE = 260,
    SQEBRACE = 261,
    OBRACE = 262,
    EBRACE = 263,
    PLUS = 264,
    MINUS = 265,
    MULTIPLY = 266,
    MOD = 267,
    SEMICOLON = 268,
    COMMA = 269,
    DOT = 270,
    NOT = 271,
    OR = 272,
    AND = 273,
    LESS = 274,
    GREATER = 275,
    EQUAL = 276,
    IFWORD = 277,
    ELSEWORD = 278,
    WHILEWORD = 279,
    INTERROGATION = 280,
    COLON = 281,
    ASSIGN = 282,
    EOFL = 283,
    STRINGWORD = 284,
    BOOLWORD = 285,
    INTWORD = 286,
    SHORTWORD = 287,
    CLASSWORD = 288,
    NEWWORD = 289,
    THISWORD = 290,
    PUBLICWORD = 291,
    PRIVATEWORD = 292,
    STATICWORD = 293,
    VOIDWORD = 294,
    RETURNWORD = 295,
    MAINWORD = 296,
    EXTENSIONWORD = 297,
    PRINTWORD = 298,
    LENGTHWORD = 299,
    TRUE = 300,
    FALSE = 301,
    IDENTIFIER = 302,
    NUM = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 53 "parser1.y" /* yacc.c:1909  */

	int Int;
	const Symbol* Symbol;//������
	const IType* Type;//��� ��������
	const Extension* Extension;//���, ����������� ���������� � ������������
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

#line 130 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
