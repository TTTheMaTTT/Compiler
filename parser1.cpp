/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 9 "parser1.y" /* yacc.c:339  */

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


#line 108 "parser1.cpp" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
#line 4 "parser1.y" /* yacc.c:355  */

#include "GrammarDeclarations.h"
#include "Symbol.h"

#line 143 "parser1.cpp" /* yacc.c:355  */

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
    ASSIGN = 280,
    EOFL = 281,
    STRINGWORD = 282,
    BOOLWORD = 283,
    INTWORD = 284,
    CLASSWORD = 285,
    NEWWORD = 286,
    THISWORD = 287,
    PUBLICWORD = 288,
    PRIVATEWORD = 289,
    STATICWORD = 290,
    VOIDWORD = 291,
    RETURNWORD = 292,
    MAINWORD = 293,
    EXTENSIONWORD = 294,
    PRINTWORD = 295,
    LENGTHWORD = 296,
    TRUE = 297,
    FALSE = 298,
    IDENTIFIER = 299,
    NUM = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 53 "parser1.y" /* yacc.c:355  */

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

#line 221 "parser1.cpp" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 250 "parser1.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   347

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   111,   111,   115,   117,   121,   127,   132,   134,   138,
     140,   144,   148,   150,   154,   160,   162,   166,   168,   170,
     174,   176,   178,   180,   184,   186,   188,   194,   196,   198,
     200,   202,   204,   208,   210,   212,   216,   218,   220,   222,
     224,   226,   228,   230,   232,   234,   236,   238,   240,   242,
     244,   246,   248,   250,   252,   254,   256,   260
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FOBRACE", "FEBRACE", "SQOBRACE",
  "SQEBRACE", "OBRACE", "EBRACE", "PLUS", "MINUS", "MULTIPLY", "MOD",
  "SEMICOLON", "COMMA", "DOT", "NOT", "OR", "AND", "LESS", "GREATER",
  "EQUAL", "IFWORD", "ELSEWORD", "WHILEWORD", "ASSIGN", "EOFL",
  "STRINGWORD", "BOOLWORD", "INTWORD", "CLASSWORD", "NEWWORD", "THISWORD",
  "PUBLICWORD", "PRIVATEWORD", "STATICWORD", "VOIDWORD", "RETURNWORD",
  "MAINWORD", "EXTENSIONWORD", "PRINTWORD", "LENGTHWORD", "TRUE", "FALSE",
  "IDENTIFIER", "NUM", "$accept", "Goal", "ClassDeclarationList",
  "MainClass", "ClassDeclaration", "Extension", "VarDeclarationList",
  "VarDeclaration", "MethodDeclarationList", "MethodDeclaration",
  "ScopeAttribute", "ArgumentList", "Type", "StatementList", "Statement",
  "ExpressionList", "Expression", "Err", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -26

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-26)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -19,   -25,    20,   -62,    22,   -62,   -12,     1,   -62,    -5,
     -62,    11,    15,    28,    25,    69,    37,   -62,   -62,    59,
     -21,    54,   -62,    78,   -62,   -62,    24,    40,    80,    82,
     -62,   -62,   -62,   -62,   -21,    77,    85,   -62,    53,   -62,
      55,    93,    95,   -21,    98,    96,    66,    58,   108,   103,
      52,   111,   113,   120,     5,   124,   -62,   -21,   -62,   130,
      23,   122,    63,    63,    63,    63,    63,   133,    49,   -62,
     -62,   -62,    23,    63,    63,   -13,   -62,   -62,   -62,   -62,
     -62,   104,   121,   138,   155,   172,   -62,     5,   107,   -62,
     189,    17,   140,   144,    63,    58,    63,    63,    63,    63,
      21,    63,    63,    63,    63,    63,    58,   139,   129,   -62,
      63,   -62,    63,   154,   206,   145,   332,   332,    17,    17,
     -62,   156,   308,   291,   321,   321,   321,   -62,   -62,    63,
     223,   240,   -62,   -62,    58,    63,   257,   165,   -62,   -62,
     163,   274,   -62,   -62,   -62,    63,   -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     0,     0,     2,     0,
       3,     0,     8,     0,     0,     0,     0,     7,    10,     0,
      13,     0,    21,    22,    23,     9,     0,     0,     0,     0,
       6,    15,    16,    12,     0,     0,     0,    20,     0,    11,
       0,     0,     0,    19,     0,     0,     0,     0,     0,    18,
       0,     0,     0,     0,     0,     0,    10,    19,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      27,    24,     0,     0,     0,     0,    52,    49,    50,    51,
      48,     0,     0,     0,     0,     0,     5,    23,     0,    26,
       0,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,    55,     0,     0,     0,     0,    36,    37,    38,    39,
      46,     0,    41,    40,    42,    43,    44,    29,    30,     0,
       0,     0,    54,    45,     0,    35,     0,     0,    53,    28,
       0,    34,    32,    14,    47,    35,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -62,   -62,   -62,   -62,   -62,   -62,   123,   -62,   -62,   -62,
     -62,   131,   -28,   -51,   -47,    33,   -61,   -62
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     3,    10,    15,    20,    25,    26,    33,
      34,    45,    27,    59,    60,   140,   141,    61
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    81,    82,    83,    84,    85,    38,    22,    23,    71,
      65,     1,    90,    91,     8,    46,    92,    88,     9,     4,
       5,    89,    94,    24,    58,     7,    50,   -25,    30,    46,
      66,    93,   100,   114,    11,   116,   117,   118,   119,    12,
     122,   123,   124,   125,   126,    51,    13,    52,   115,   130,
      58,   131,    50,    58,    14,    50,   -25,    31,    32,   127,
     -25,    50,   120,    53,    16,   121,    21,    54,   136,    17,
      73,    51,    18,    52,    51,    19,    52,    22,    23,    74,
      51,    28,    52,    29,    35,    36,   -25,   139,    37,    53,
      39,    40,    53,    87,    75,    76,    54,    41,    53,    42,
      43,    47,    54,    44,    48,    77,    78,    79,    80,    94,
      49,    56,    95,    96,    97,    98,    99,    57,    62,   100,
      63,   101,   102,   103,   104,   105,    94,    64,    67,   106,
      96,    97,    98,    99,    70,    72,   100,    86,   101,   102,
     103,   104,   105,    94,   110,   112,   107,    96,    97,    98,
      99,   113,   128,   100,   129,   101,   102,   103,   104,   105,
      94,   108,   132,   135,    96,    97,    98,    99,   134,   143,
     100,   144,   101,   102,   103,   104,   105,    94,   146,    68,
       0,    96,    97,    98,    99,   109,     0,   100,    69,   101,
     102,   103,   104,   105,    94,     0,     0,   111,    96,    97,
      98,    99,     0,     0,   100,     0,   101,   102,   103,   104,
     105,    94,   133,     0,     0,    96,    97,    98,    99,     0,
       0,   100,     0,   101,   102,   103,   104,   105,    94,     0,
       0,     0,    96,    97,    98,    99,   137,     0,   100,     0,
     101,   102,   103,   104,   105,    94,   138,     0,     0,    96,
      97,    98,    99,     0,     0,   100,     0,   101,   102,   103,
     104,   105,    94,     0,     0,     0,    96,    97,    98,    99,
     142,     0,   100,     0,   101,   102,   103,   104,   105,    94,
       0,     0,     0,    96,    97,    98,    99,     0,   145,   100,
       0,   101,   102,   103,   104,   105,    94,     0,     0,     0,
      96,    97,    98,    99,     0,     0,   100,     0,   101,   -26,
     103,   104,   105,    94,     0,     0,     0,    96,    97,    98,
      99,     0,     0,   100,     0,   -26,    94,   103,   104,   105,
      96,    97,    98,    99,     0,     0,   100,    94,     0,     0,
     -26,   -26,   -26,    98,    99,     0,     0,   100
};

static const yytype_int16 yycheck[] =
{
      47,    62,    63,    64,    65,    66,    34,    28,    29,    60,
       5,    30,    73,    74,    26,    43,    29,    68,    30,    44,
       0,    72,     5,    44,     1,     3,     3,     4,     4,    57,
      25,    44,    15,    94,    33,    96,    97,    98,    99,    44,
     101,   102,   103,   104,   105,    22,    35,    24,    95,   110,
       1,   112,     3,     1,    39,     3,     4,    33,    34,   106,
      37,     3,    41,    40,    36,    44,     7,    44,   129,    44,
       7,    22,     3,    24,    22,    38,    24,    28,    29,    16,
      22,    27,    24,     5,    44,     5,    37,   134,     6,    40,
      13,     6,    40,    44,    31,    32,    44,    44,    40,    44,
       7,     3,    44,     8,     8,    42,    43,    44,    45,     5,
      44,     3,     8,     9,    10,    11,    12,    14,     7,    15,
       7,    17,    18,    19,    20,    21,     5,     7,     4,     8,
       9,    10,    11,    12,     4,    13,    15,     4,    17,    18,
      19,    20,    21,     5,    37,     5,     8,     9,    10,    11,
      12,     7,    13,    15,    25,    17,    18,    19,    20,    21,
       5,     6,     8,     7,     9,    10,    11,    12,    23,     4,
      15,     8,    17,    18,    19,    20,    21,     5,   145,    56,
      -1,     9,    10,    11,    12,    13,    -1,    15,    57,    17,
      18,    19,    20,    21,     5,    -1,    -1,     8,     9,    10,
      11,    12,    -1,    -1,    15,    -1,    17,    18,    19,    20,
      21,     5,     6,    -1,    -1,     9,    10,    11,    12,    -1,
      -1,    15,    -1,    17,    18,    19,    20,    21,     5,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    -1,    15,    -1,
      17,    18,    19,    20,    21,     5,     6,    -1,    -1,     9,
      10,    11,    12,    -1,    -1,    15,    -1,    17,    18,    19,
      20,    21,     5,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,     5,
      -1,    -1,    -1,     9,    10,    11,    12,    -1,    14,    15,
      -1,    17,    18,    19,    20,    21,     5,    -1,    -1,    -1,
       9,    10,    11,    12,    -1,    -1,    15,    -1,    17,    18,
      19,    20,    21,     5,    -1,    -1,    -1,     9,    10,    11,
      12,    -1,    -1,    15,    -1,    17,     5,    19,    20,    21,
       9,    10,    11,    12,    -1,    -1,    15,     5,    -1,    -1,
      19,    20,    21,    11,    12,    -1,    -1,    15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    47,    49,    44,     0,    48,     3,    26,    30,
      50,    33,    44,    35,    39,    51,    36,    44,     3,    38,
      52,     7,    28,    29,    44,    53,    54,    58,    27,     5,
       4,    33,    34,    55,    56,    44,     5,     6,    58,    13,
       6,    44,    44,     7,     8,    57,    58,     3,     8,    44,
       3,    22,    24,    40,    44,    60,     3,    14,     1,    59,
      60,    63,     7,     7,     7,     5,    25,     4,    52,    57,
       4,    59,    13,     7,    16,    31,    32,    42,    43,    44,
      45,    62,    62,    62,    62,    62,     4,    44,    59,    59,
      62,    62,    29,    44,     5,     8,     9,    10,    11,    12,
      15,    17,    18,    19,    20,    21,     8,     8,     6,    13,
      37,     8,     5,     7,    62,    60,    62,    62,    62,    62,
      41,    44,    62,    62,    62,    62,    62,    60,    13,    25,
      62,    62,     8,     6,    23,     7,    62,    13,     6,    60,
      61,    62,    13,     4,     8,    14,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    50,    51,    51,    52,
      52,    53,    54,    54,    55,    56,    56,    57,    57,    57,
      58,    58,    58,    58,    59,    59,    59,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     0,    17,     7,     2,     0,     2,
       0,     3,     2,     0,    13,     1,     1,     4,     2,     0,
       3,     1,     1,     1,     2,     0,     3,     3,     7,     5,
       5,     4,     7,     3,     1,     0,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     6,     1,     1,
       1,     1,     1,     5,     4,     3,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 111 "parser1.y" /* yacc.c:1646  */
    {prog=(yyval.Program)=new Program((yyvsp[-2].MainClass),(yyvsp[-1].ClassDeclarationList)); 	printf("Всё хорошо\n");}
#line 1537 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 115 "parser1.y" /* yacc.c:1646  */
    {(yyval.ClassDeclarationList)=new AddClassDeclarationList((yyvsp[-1].ClassDeclarationList),(yyvsp[0].ClassDeclaration));}
#line 1543 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 117 "parser1.y" /* yacc.c:1646  */
    {(yyval.ClassDeclarationList)=new EmptyClassDeclarationList();}
#line 1549 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 123 "parser1.y" /* yacc.c:1646  */
    {(yyval.MainClass)=new IMainClass((yyvsp[-15].Symbol),(yyvsp[-5].Symbol),(yyvsp[-2].Statement));}
#line 1555 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 128 "parser1.y" /* yacc.c:1646  */
    {(yyval.ClassDeclaration)=new IClassDeclaration((yyvsp[-5].Symbol),(yyvsp[-4].Extension),(yyvsp[-2].VarDeclarationList),(yyvsp[-1].MethodDeclarationList),yylloc.first_line);}
#line 1561 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 132 "parser1.y" /* yacc.c:1646  */
    {(yyval.Extension)=new Extension((yyvsp[0].Symbol),yylloc.first_line);}
#line 1567 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 134 "parser1.y" /* yacc.c:1646  */
    {(yyval.Extension)=new Extension();}
#line 1573 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 138 "parser1.y" /* yacc.c:1646  */
    {(yyval.VarDeclarationList)=new AddVarDeclarationList((yyvsp[-1].VarDeclarationList),(yyvsp[0].VarDeclaration));}
#line 1579 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 140 "parser1.y" /* yacc.c:1646  */
    {(yyval.VarDeclarationList)=new EmptyVarDeclarationList();}
#line 1585 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 144 "parser1.y" /* yacc.c:1646  */
    {(yyval.VarDeclaration)=new IVarDeclaration((yyvsp[-2].Type),(yyvsp[-1].Symbol),yylloc.first_line);}
#line 1591 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 148 "parser1.y" /* yacc.c:1646  */
    {(yyval.MethodDeclarationList)=new AddMethodDeclarationList((yyvsp[-1].MethodDeclarationList),(yyvsp[0].MethodDeclaration));}
#line 1597 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 150 "parser1.y" /* yacc.c:1646  */
    {(yyval.MethodDeclarationList)=new EmptyMethodDeclarationList();}
#line 1603 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 156 "parser1.y" /* yacc.c:1646  */
    {(yyval.MethodDeclaration)=new IMethodDeclaration((yyvsp[-11].Type),(yyvsp[-10].Symbol),(yyvsp[-8].ArgumentList),(yyvsp[-5].VarDeclarationList),(yyvsp[-4].StatementList),(yyvsp[-2].Exp),yylloc.first_line);}
#line 1609 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 166 "parser1.y" /* yacc.c:1646  */
    {(yyval.ArgumentList)=new AddArgumentList((yyvsp[-3].Type),(yyvsp[-2].Symbol),(yyvsp[0].ArgumentList),yylloc.first_line);}
#line 1615 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 168 "parser1.y" /* yacc.c:1646  */
    {(yyval.ArgumentList)=new OnlyArgumentList((yyvsp[-1].Type),(yyvsp[0].Symbol),yylloc.first_line);}
#line 1621 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 170 "parser1.y" /* yacc.c:1646  */
    {(yyval.ArgumentList)=new ZeroArgumentList();}
#line 1627 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 174 "parser1.y" /* yacc.c:1646  */
    {(yyval.Type)=new IType(getIntern("array of int"));}
#line 1633 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 176 "parser1.y" /* yacc.c:1646  */
    {(yyval.Type)=new IType(getIntern("bool"));}
#line 1639 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 178 "parser1.y" /* yacc.c:1646  */
    {(yyval.Type)=new IType(getIntern("int"));}
#line 1645 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 180 "parser1.y" /* yacc.c:1646  */
    {(yyval.Type)=new IType((yyvsp[0].Symbol));}
#line 1651 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 184 "parser1.y" /* yacc.c:1646  */
    {(yyval.StatementList)=new AddStatementList((yyvsp[-1].Statement),(yyvsp[0].StatementList));}
#line 1657 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 186 "parser1.y" /* yacc.c:1646  */
    {(yyval.StatementList)=new EmptyStatementList();}
#line 1663 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 188 "parser1.y" /* yacc.c:1646  */
    {(yyval.StatementList)=new ErrorStatementList((yyvsp[0].StatementList));
								//yyerror("Syntax Error");
								}
#line 1671 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 194 "parser1.y" /* yacc.c:1646  */
    {(yyval.Statement)=new CompoundStatement((yyvsp[-1].StatementList),yylloc.first_line);}
#line 1677 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 196 "parser1.y" /* yacc.c:1646  */
    {(yyval.Statement)=new ConditionalStatement((yyvsp[-4].Exp),(yyvsp[-2].Statement),(yyvsp[0].Statement),yylloc.first_line);}
#line 1683 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 198 "parser1.y" /* yacc.c:1646  */
    {(yyval.Statement)=new CycleStatement((yyvsp[-2].Exp),(yyvsp[0].Statement),yylloc.first_line);}
#line 1689 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 200 "parser1.y" /* yacc.c:1646  */
    {(yyval.Statement)=new PrintStatement((yyvsp[-2].Exp),yylloc.first_line);}
#line 1695 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 202 "parser1.y" /* yacc.c:1646  */
    {(yyval.Statement)=new AssignStatement((yyvsp[-3].Symbol),(yyvsp[-1].Exp),yylloc.first_line);}
#line 1701 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 204 "parser1.y" /* yacc.c:1646  */
    {(yyval.Statement)=new AssignArrayElementStatement((yyvsp[-6].Symbol),(yyvsp[-4].Exp),(yyvsp[-1].Exp),yylloc.first_line);}
#line 1707 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 208 "parser1.y" /* yacc.c:1646  */
    {(yyval.ExpList)=new AddExpList((yyvsp[-2].Exp),(yyvsp[0].ExpList));}
#line 1713 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 210 "parser1.y" /* yacc.c:1646  */
    {(yyval.ExpList)=new OnlyExpList((yyvsp[0].Exp));}
#line 1719 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 212 "parser1.y" /* yacc.c:1646  */
    {(yyval.ExpList)=new ZeroExpList();}
#line 1725 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 216 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::PLUS);}
#line 1731 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 218 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::MINUS);}
#line 1737 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 220 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::MULTIPLY);}
#line 1743 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 222 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::MOD);}
#line 1749 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 224 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::AND);}
#line 1755 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 226 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::OR);}
#line 1761 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 228 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::LESS);}
#line 1767 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 230 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::GREATER);}
#line 1773 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 232 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BinopExp((yyvsp[-2].Exp),(yyvsp[0].Exp),yylloc.first_line,binOpType::EQUAL);}
#line 1779 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 234 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new GetArrayElementExp((yyvsp[-3].Exp),(yyvsp[-1].Exp),yylloc.first_line);}
#line 1785 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 236 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new GetLengthExp((yyvsp[-2].Exp),yylloc.first_line);}
#line 1791 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 238 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new MethodExp((yyvsp[-5].Exp),(yyvsp[-3].Symbol),(yyvsp[-1].ExpList),yylloc.first_line);}
#line 1797 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 240 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new NumExp((yyvsp[0].Int),yylloc.first_line);}
#line 1803 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 242 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BoolExp(true,yylloc.first_line);}
#line 1809 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 244 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new BoolExp(false,yylloc.first_line);}
#line 1815 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 246 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new IDExp((yyvsp[0].Symbol),yylloc.first_line);}
#line 1821 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 248 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new ThisExp();}
#line 1827 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 250 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new GetArrayExp((yyvsp[-1].Exp),yylloc.first_line);}
#line 1833 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 252 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new NewObjectExp((yyvsp[-2].Symbol),yylloc.first_line);}
#line 1839 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 254 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new EnclosedExp((yyvsp[-1].Exp),yylloc.first_line);}
#line 1845 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 256 "parser1.y" /* yacc.c:1646  */
    {(yyval.Exp)=new NegativeExp((yyvsp[0].Exp),yylloc.first_line);}
#line 1851 "parser1.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 260 "parser1.y" /* yacc.c:1646  */
    {yyerror("Syntax Error");}
#line 1857 "parser1.cpp" /* yacc.c:1646  */
    break;


#line 1861 "parser1.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 262 "parser1.y" /* yacc.c:1906  */


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
