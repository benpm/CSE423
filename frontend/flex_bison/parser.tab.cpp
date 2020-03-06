/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "frontend/flex_bison/parser.ypp"

    #include <vector>
    #include <spdlog/spdlog.h>
    #include <spdlog/sinks/stdout_color_sinks.h>
    #include <spdlog/fmt/fmt.h>
    #include <parsetree.hpp>

    extern int yylex();
    extern int yyparse();

    void yyerror(const char *s);

    PTNode* pt;

#line 85 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_HOME_SUPA_LIN_STORAGE_CSE423_FRONTEND_FLEX_BISON_PARSER_TAB_HPP_INCLUDED
# define YY_YY_HOME_SUPA_LIN_STORAGE_CSE423_FRONTEND_FLEX_BISON_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    CHAR = 260,
    FOR = 261,
    WHILE = 262,
    IF = 263,
    ELSE = 264,
    RETURN = 265,
    BREAK = 266,
    SEMICOLON = 267,
    COMMA = 268,
    LPAREN = 269,
    RPAREN = 270,
    LBRACE = 271,
    RBRACE = 272,
    LBRACK = 273,
    RBRACK = 274,
    EQUAL = 275,
    PLUS = 276,
    MINUS = 277,
    TIMES = 278,
    DIVIDE = 279,
    MODULO = 280,
    PLUSEQUAL = 281,
    MINUSEQUAL = 282,
    TIMESEQUAL = 283,
    DIVEQUAL = 284,
    MODEQUAL = 285,
    INCR = 286,
    DECR = 287,
    LT = 288,
    GT = 289,
    LE = 290,
    GE = 291,
    ISEQ = 292,
    NOTEQ = 293,
    LOGAND = 294,
    LOGOR = 295,
    NOT = 296,
    STRINGLIT = 297,
    CHARLIT = 298,
    INTCONST = 299,
    FLOATCONST = 300,
    ID = 301,
    UNKNOWN = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "frontend/flex_bison/parser.ypp"

    int ival;
    float fval;
    char *sval;
    char cval;
    PTNode* pt;

#line 184 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
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

#endif /* !YY_YY_HOME_SUPA_LIN_STORAGE_CSE423_FRONTEND_FLEX_BISON_PARSER_TAB_HPP_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   196

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

#define YYUNDEFTOK  2
#define YYMAXUTOK   302

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   140,   140,   147,   152,   159,   164,   171,   178,   185,
     190,   197,   202,   210,   215,   219,   226,   233,   237,   241,
     247,   254,   261,   266,   272,   277,   284,   289,   296,   301,
     306,   311,   316,   321,   328,   333,   339,   344,   349,   356,
     361,   368,   373,   380,   384,   388,   392,   396,   400,   406,
     410,   416,   422,   429,   435,   442,   448,   455,   460,   467,
     471,   475,   479,   483,   487,   493,   498,   505,   509,   515,
     520,   527,   531,   535,   541,   546,   553,   560,   565,   572,
     577,   582,   589,   598,   603,   609,   614,   621,   626,   631,
     636,   643,   650,   655,   661,   666,   672,   678,   686,   694,
     700,   706,   711,   718,   725,   732,   736,   743
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "CHAR", "FOR", "WHILE",
  "IF", "ELSE", "RETURN", "BREAK", "SEMICOLON", "COMMA", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "EQUAL", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "MODULO", "PLUSEQUAL", "MINUSEQUAL",
  "TIMESEQUAL", "DIVEQUAL", "MODEQUAL", "INCR", "DECR", "LT", "GT", "LE",
  "GE", "ISEQ", "NOTEQ", "LOGAND", "LOGOR", "NOT", "STRINGLIT", "CHARLIT",
  "INTCONST", "FLOATCONST", "ID", "UNKNOWN", "$accept", "program",
  "declarationList", "declaration", "varDeclaration",
  "scopedVarDeclaration", "varDeclList", "varDeclInitialize", "varDeclId",
  "scopedTypeSpecifier", "typeSpecifier", "funName", "funDeclaration",
  "params", "paramList", "paramId", "statement", "expressionStmt",
  "expression", "unaryAssignExpr", "mutable", "assignop", "unaryAssignop",
  "simpleExpression", "andExpression", "unaryRelExpression",
  "relExpression", "relop", "sumExpression", "sumop", "mulExpression",
  "mulop", "unaryExpression", "unaryMinus", "factor", "immutable", "call",
  "args", "argList", "constant", "compoundStmt", "localDeclarations",
  "statementList", "selectionStmt", "elseStmt", "elseIfList",
  "iterationStmt", "whileStmt", "forStmt", "returnStmt", "breakStmt", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

#define YYPACT_NINF -105

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-105)))

#define YYTABLE_NINF -21

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      54,  -105,  -105,  -105,     2,    54,  -105,  -105,   -24,  -105,
    -105,  -105,     5,    12,  -105,    22,    49,   118,  -105,    23,
      42,    54,  -105,  -105,  -105,  -105,  -105,    56,    62,  -105,
     113,    -5,    42,    64,    75,    55,    58,  -105,  -105,   143,
      89,  -105,  -105,  -105,  -105,  -105,  -105,    53,    94,   105,
    -105,  -105,  -105,   108,  -105,   164,    74,    55,  -105,  -105,
     113,   113,    42,    42,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,    -5,    -5,  -105,  -105,  -105,    -5,   112,  -105,
      60,    54,  -105,  -105,  -105,  -105,  -105,  -105,  -105,   113,
    -105,  -105,    75,  -105,   110,   119,   114,    58,  -105,   -14,
      89,  -105,   115,   117,   122,   126,   107,   129,  -105,  -105,
    -105,  -105,   130,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
      53,  -105,  -105,   113,  -105,  -105,    54,    42,    42,  -105,
     134,  -105,    54,  -105,  -105,  -105,    -5,    23,   -11,    13,
    -105,  -105,    23,  -105,     4,   135,    60,   150,    77,  -105,
    -105,   113,  -105,  -105,  -105,   111,   158,    60,    65,  -105,
    -105,   154,  -105,    42,    15,   150,  -105
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    17,    18,    19,     0,     2,     4,     5,     0,     6,
       1,     3,    13,     0,    10,    11,     0,     0,     7,     0,
       0,    23,    14,    87,    88,    90,    89,     0,    13,     9,
       0,     0,     0,    41,    78,    12,    52,    54,    56,    58,
      66,    70,    74,    75,    77,    80,    81,     0,     0,    22,
      15,    49,    50,     0,    37,    78,     0,    38,    76,    55,
      84,     0,     0,     0,    67,    68,    60,    61,    59,    62,
      63,    64,     0,     0,    71,    72,    73,     0,    26,    25,
       0,     0,    79,    43,    44,    45,    46,    47,    48,     0,
      40,    41,    39,    86,     0,    83,     0,    51,    53,    57,
      65,    69,     0,     0,     0,     0,     0,     0,    35,    93,
      21,    28,     0,    29,    30,    31,   101,   102,    32,    33,
       0,    36,    82,     0,    42,    27,     0,     0,     0,   105,
       0,   107,    95,    34,    24,    85,     0,     0,     0,     0,
     106,    92,     0,    16,     0,     0,     0,     0,     0,    91,
      94,     0,   103,   100,     8,     0,    96,     0,     0,    97,
     104,     0,    98,     0,     0,     0,    99
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -105,  -105,  -105,   165,    43,  -105,    29,   153,  -105,  -105,
     -16,  -105,  -105,  -105,  -105,    63,   -46,  -105,   -27,  -105,
     -29,  -105,   120,   -20,   123,   -19,    37,  -105,   102,  -105,
     116,  -105,   -25,  -105,  -105,  -105,  -105,  -105,  -105,   169,
    -104,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,   141,    13,    14,    15,   142,
       8,    16,     9,    48,    49,    79,   110,   111,   112,    54,
      34,    89,    56,    57,    36,    37,    38,    72,    39,    73,
      40,    77,    41,    42,    43,    44,    45,    94,    95,    46,
     113,   132,   144,   114,   159,   156,   115,   116,   117,   118,
     119
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    55,    10,    53,   146,    47,    58,    64,    65,    30,
     103,   104,   105,    59,   106,   107,   108,    31,    30,   -20,
     109,   149,    12,    17,    18,    19,    31,    92,   147,    62,
     165,    55,    55,    93,    96,    51,    52,    23,    24,    25,
      26,    33,    20,   153,    98,    32,    23,    24,    25,    26,
      33,    55,   101,    62,   162,    62,    30,     1,     2,     3,
      55,   166,   121,    21,    31,   120,   103,   104,   105,    28,
     106,   107,   108,   161,    30,    50,   109,    55,    60,   130,
      17,   109,    31,    32,    23,    24,    25,    26,    33,   154,
      19,    51,    52,    61,    55,    62,   135,    63,   150,    78,
     152,    32,    23,    24,    25,    26,    33,   138,   139,    80,
     137,   160,    74,    75,    76,    55,   143,    55,    81,   129,
      91,    30,    55,    82,   155,   122,   157,    30,    55,    31,
     102,   126,   123,   124,   125,    31,   127,    22,    51,    52,
     128,   131,   133,   164,    51,    52,   140,   151,    32,    23,
      24,    25,    26,    33,    32,    23,    24,    25,    26,    33,
      23,    24,    25,    26,    64,    65,   109,   158,   163,   136,
      11,   148,    29,   145,    99,    90,    66,    67,    68,    69,
      70,    71,    61,   134,    83,    97,    27,     0,     0,   100,
      84,    85,    86,    87,    88,    51,    52
};

static const yytype_int16 yycheck[] =
{
      20,    30,     0,    30,    15,    21,    31,    21,    22,    14,
       6,     7,     8,    32,    10,    11,    12,    22,    14,    14,
      16,    17,    46,    18,    12,    13,    22,    56,    15,    40,
      15,    60,    61,    60,    61,    31,    32,    42,    43,    44,
      45,    46,    20,   147,    63,    41,    42,    43,    44,    45,
      46,    80,    77,    40,   158,    40,    14,     3,     4,     5,
      89,   165,    89,    14,    22,    81,     6,     7,     8,    46,
      10,    11,    12,     8,    14,    19,    16,   106,    14,   106,
      18,    16,    22,    41,    42,    43,    44,    45,    46,    12,
      13,    31,    32,    18,   123,    40,   123,    39,   144,    46,
     146,    41,    42,    43,    44,    45,    46,   127,   128,    15,
     126,   157,    23,    24,    25,   144,   132,   146,    13,    12,
      46,    14,   151,    15,   151,    15,    15,    14,   157,    22,
      18,    14,    13,    19,    19,    22,    14,    19,    31,    32,
      14,    12,    12,   163,    31,    32,    12,    12,    41,    42,
      43,    44,    45,    46,    41,    42,    43,    44,    45,    46,
      42,    43,    44,    45,    21,    22,    16,     9,    14,   126,
       5,   142,    19,   136,    72,    55,    33,    34,    35,    36,
      37,    38,    18,   120,    20,    62,    17,    -1,    -1,    73,
      26,    27,    28,    29,    30,    31,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    49,    50,    51,    52,    58,    60,
       0,    51,    46,    54,    55,    56,    59,    18,    12,    13,
      20,    14,    19,    42,    43,    44,    45,    87,    46,    55,
      14,    22,    41,    46,    68,    71,    72,    73,    74,    76,
      78,    80,    81,    82,    83,    84,    87,    58,    61,    62,
      19,    31,    32,    66,    67,    68,    70,    71,    80,    73,
      14,    18,    40,    39,    21,    22,    33,    34,    35,    36,
      37,    38,    75,    77,    23,    24,    25,    79,    46,    63,
      15,    13,    15,    20,    26,    27,    28,    29,    30,    69,
      70,    46,    68,    66,    85,    86,    66,    72,    73,    76,
      78,    80,    18,     6,     7,     8,    10,    11,    12,    16,
      64,    65,    66,    88,    91,    94,    95,    96,    97,    98,
      58,    66,    15,    13,    19,    19,    14,    14,    14,    12,
      66,    12,    89,    12,    63,    66,    52,    58,    71,    71,
      12,    53,    57,    58,    90,    74,    15,    15,    54,    17,
      64,    12,    64,    88,    12,    66,    93,    15,     9,    92,
      64,     8,    88,    14,    71,    15,    88
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    53,    54,
      54,    55,    55,    56,    56,    56,    57,    58,    58,    58,
      59,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      64,    64,    64,    64,    65,    65,    66,    66,    66,    67,
      67,    68,    68,    69,    69,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    75,    75,    75,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    79,    80,    80,    81,    82,    82,    83,
      83,    83,    84,    85,    85,    86,    86,    87,    87,    87,
      87,    88,    89,    89,    90,    90,    91,    91,    92,    93,
      93,    94,    94,    95,    96,    97,    97,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     3,     3,
       1,     1,     3,     1,     3,     4,     1,     1,     1,     1,
       1,     6,     1,     0,     4,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     1,     1,     2,
       2,     1,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       1,     1,     4,     1,     0,     3,     1,     1,     1,     1,
       1,     4,     2,     0,     2,     0,     6,     7,     2,     7,
       0,     1,     1,     5,     8,     2,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 141 "frontend/flex_bison/parser.ypp"
    {
            pt = new PTNode(PTNode::PROGRAM,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1530 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 3:
#line 148 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::DECLARATION_LIST,
                std::vector<PTNode*> { (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1539 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 4:
#line 153 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::DECLARATION_LIST,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1548 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 5:
#line 160 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::DECLARATION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1557 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 6:
#line 165 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::DECLARATION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1566 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 7:
#line 172 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::VAR_DECLARATION,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 1575 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 8:
#line 179 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::SCOPED_VAR_DECLARATION,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 1584 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 9:
#line 186 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::VAR_DECL_LIST,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1593 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 10:
#line 191 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::VAR_DECL_LIST,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1602 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 11:
#line 198 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::VAR_DECL_INITIALIZE,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1611 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 12:
#line 203 "frontend/flex_bison/parser.ypp"
    {
            PTNode *nEQUAL = new PTNode(PTNode::EQUAL, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::VAR_DECL_INITIALIZE,
                std::vector<PTNode*> { (yyvsp[-2].pt), nEQUAL, (yyvsp[0].pt)}, yylloc.first_line);
        }
#line 1621 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 13:
#line 211 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ID, yylloc.first_line);
            (yyval.pt)->data.sval = (yyvsp[0].sval);
        }
#line 1630 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 14:
#line 216 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ARRAY_ID, yylloc.first_line);
        }
#line 1638 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 15:
#line 220 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::VAR_DECL_ID,
                std::vector<PTNode*> { (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 1647 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 16:
#line 227 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::SCOPED_TYPE_SPECIFIER,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1656 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 17:
#line 234 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::INT, yylloc.first_line);
        }
#line 1664 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 18:
#line 238 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::FLOAT, yylloc.first_line);
        }
#line 1672 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 19:
#line 242 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::CHAR, yylloc.first_line);
        }
#line 1680 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 20:
#line 248 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ID, yylloc.first_line);
            (yyval.pt)->data.sval = (yyvsp[0].sval);
        }
#line 1689 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 21:
#line 255 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::FUN_DECLARATION,
                std::vector<PTNode*> { (yyvsp[-5].pt), (yyvsp[-4].pt), (yyvsp[-2].pt), (yyvsp[0].pt)}, yylloc.first_line);
        }
#line 1698 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 22:
#line 262 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::PARAMS,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1707 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 23:
#line 267 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::PARAMS, yylloc.first_line);
        }
#line 1715 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 24:
#line 273 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::PARAM_LIST,
                std::vector<PTNode*> { (yyvsp[-3].pt), (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1724 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 25:
#line 278 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::PARAM_LIST,
                std::vector<PTNode*> { (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1733 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 26:
#line 285 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ID, yylloc.first_line);
            (yyval.pt)->data.sval = (yyvsp[0].sval);
        }
#line 1742 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 27:
#line 290 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ID, yylloc.first_line);
            (yyval.pt)->data.sval = (yyvsp[-2].sval);
        }
#line 1751 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 28:
#line 297 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STATEMENT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1760 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 29:
#line 302 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STATEMENT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1769 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 30:
#line 307 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STATEMENT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1778 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 31:
#line 312 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STATEMENT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1787 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 32:
#line 317 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STATEMENT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1796 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 33:
#line 322 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STATEMENT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1805 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 34:
#line 329 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::EXPRESSION_STMT,
                std::vector<PTNode*> { (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 1814 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 35:
#line 334 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode();
        }
#line 1822 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 36:
#line 340 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1831 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 37:
#line 345 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1840 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 38:
#line 350 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1849 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 39:
#line 357 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::UNARY_ASSIGN_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1858 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 40:
#line 362 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::UNARY_ASSIGN_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1867 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 41:
#line 369 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ID, yylloc.first_line);
            (yyval.pt)->data.sval = (yyvsp[0].sval);
        }
#line 1876 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 42:
#line 374 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::MUTABLE,
                std::vector<PTNode*> { (yyvsp[-3].pt), (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 1885 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 43:
#line 381 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::EQUAL, yylloc.first_line);
        }
#line 1893 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 44:
#line 385 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::PLUSEQUAL, yylloc.first_line);
        }
#line 1901 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 45:
#line 389 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::MINUSEQUAL, yylloc.first_line);
        }
#line 1909 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 46:
#line 393 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::TIMESEQUAL, yylloc.first_line);
        }
#line 1917 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 47:
#line 397 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::DIVEQUAL, yylloc.first_line);
        }
#line 1925 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 48:
#line 401 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::MODEQUAL, yylloc.first_line);
        }
#line 1933 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 49:
#line 407 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::INCR, yylloc.first_line);
        }
#line 1941 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 50:
#line 411 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::DECR, yylloc.first_line);
        }
#line 1949 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 51:
#line 417 "frontend/flex_bison/parser.ypp"
    {
            PTNode* nLOGOR = new PTNode(PTNode::LOGOR, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::SIMPLE_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-2].pt), nLOGOR, (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1959 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 52:
#line 423 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::SIMPLE_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1968 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 53:
#line 430 "frontend/flex_bison/parser.ypp"
    {
            PTNode* nLOGAND = new PTNode(PTNode::LOGAND, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::AND_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-2].pt), nLOGAND, (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1978 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 54:
#line 436 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::AND_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1987 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 55:
#line 443 "frontend/flex_bison/parser.ypp"
    {
            PTNode* nNOT = new PTNode(PTNode::NOT, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::UNARY_REL_EXPRESSION,
                std::vector<PTNode*> { nNOT, (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 1997 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 56:
#line 449 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::UNARY_REL_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2006 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 57:
#line 456 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::REL_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2015 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 58:
#line 461 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::REL_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2024 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 59:
#line 468 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::LE, yylloc.first_line);
        }
#line 2032 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 60:
#line 472 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::LT, yylloc.first_line);
        }
#line 2040 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 61:
#line 476 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::GT, yylloc.first_line);
        }
#line 2048 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 62:
#line 480 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::GE, yylloc.first_line);
        }
#line 2056 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 63:
#line 484 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ISEQ, yylloc.first_line);
        }
#line 2064 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 64:
#line 488 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::NOTEQ, yylloc.first_line);
        }
#line 2072 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 65:
#line 494 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::SUM_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2081 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 66:
#line 499 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::SUM_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2090 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 67:
#line 506 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::PLUS, yylloc.first_line);
        }
#line 2098 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 68:
#line 510 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::MINUS, yylloc.first_line);
        }
#line 2106 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 69:
#line 516 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::MUL_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2115 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 70:
#line 521 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::MUL_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2124 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 71:
#line 528 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::TIMES, yylloc.first_line);
        }
#line 2132 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 72:
#line 532 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::DIVIDE, yylloc.first_line);
        }
#line 2140 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 73:
#line 536 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::MODULO, yylloc.first_line);
        }
#line 2148 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 74:
#line 542 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::UNARY_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2157 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 75:
#line 547 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::UNARY_EXPRESSION,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2166 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 76:
#line 554 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::UNARY_MINUS,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2175 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 77:
#line 561 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::FACTOR,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2184 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 78:
#line 566 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::FACTOR,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2193 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 79:
#line 573 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::IMMUTABLE,
                std::vector<PTNode*> { (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 2202 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 80:
#line 578 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::IMMUTABLE,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2211 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 81:
#line 583 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::IMMUTABLE,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2220 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 82:
#line 590 "frontend/flex_bison/parser.ypp"
    {
            PTNode* tID = new PTNode(PTNode::ID, yylloc.first_line);
            tID->data.sval = (yyvsp[-3].sval);
            (yyval.pt) = new PTNode(PTNode::CALL,
                std::vector<PTNode*> { tID, (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 2231 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 83:
#line 599 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ARGS,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2240 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 84:
#line 604 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode();
        }
#line 2248 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 85:
#line 610 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ARG_LIST,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2257 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 86:
#line 615 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ARG_LIST,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2266 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 87:
#line 622 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STRINGLIT, yylloc.first_line);
            (yyval.pt)->data.sval = (yyvsp[0].sval);
        }
#line 2275 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 88:
#line 627 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::CHARLIT, yylloc.first_line);
            (yyval.pt)->data.cval = (yyvsp[0].cval);
        }
#line 2284 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 89:
#line 632 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::FLOATCONST, yylloc.first_line);
            (yyval.pt)->data.fval = (yyvsp[0].fval);
        }
#line 2293 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 90:
#line 637 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::INTCONST, yylloc.first_line);
            (yyval.pt)->data.ival = (yyvsp[0].ival);
        }
#line 2302 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 91:
#line 644 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::COMPOUND_STMT,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 2311 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 92:
#line 651 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::LOCAL_DECLARATIONS,
                std::vector<PTNode*> { (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2320 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 93:
#line 656 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode();
        }
#line 2328 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 94:
#line 662 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::STATEMENT_LIST,
                std::vector<PTNode*> { (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2337 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 95:
#line 667 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode();
        }
#line 2345 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 96:
#line 673 "frontend/flex_bison/parser.ypp"
    {
            PTNode* tIF = new PTNode(PTNode::IF, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::SELECTION_STMT,
                std::vector<PTNode*> { tIF, (yyvsp[-3].pt), (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2355 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 97:
#line 679 "frontend/flex_bison/parser.ypp"
    {
            PTNode* tIF = new PTNode(PTNode::IF, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::SELECTION_STMT,
                std::vector<PTNode*> { tIF, (yyvsp[-4].pt), (yyvsp[-2].pt), (yyvsp[-1].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2365 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 98:
#line 687 "frontend/flex_bison/parser.ypp"
    {
            PTNode* tELSE = new PTNode(PTNode::ELSE, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::ELSE_STMT,
                std::vector<PTNode*> { tELSE, (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2375 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 99:
#line 695 "frontend/flex_bison/parser.ypp"
    {
            PTNode* tELSEIF = new PTNode(PTNode::ELSE_IF, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::ELSE_IF_LIST,
                std::vector<PTNode*> { (yyvsp[-6].pt), tELSEIF, (yyvsp[-2].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2385 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 100:
#line 701 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode();
        }
#line 2393 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 101:
#line 707 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ITERATION_STMT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2402 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 102:
#line 712 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::ITERATION_STMT,
                std::vector<PTNode*> { (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2411 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 103:
#line 719 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::WHILE_STMT,
                std::vector<PTNode*> { (yyvsp[-2].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2420 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 104:
#line 726 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::FOR_STMT,
                std::vector<PTNode*> { (yyvsp[-5].pt), (yyvsp[-4].pt), (yyvsp[-2].pt), (yyvsp[0].pt) }, yylloc.first_line);
        }
#line 2429 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 105:
#line 733 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::RETURN_STMT, yylloc.first_line);
        }
#line 2437 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 106:
#line 737 "frontend/flex_bison/parser.ypp"
    {
            (yyval.pt) = new PTNode(PTNode::RETURN_STMT,
                std::vector<PTNode*> { (yyvsp[-1].pt) }, yylloc.first_line);
        }
#line 2446 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;

  case 107:
#line 744 "frontend/flex_bison/parser.ypp"
    {
            PTNode* tBREAK = new PTNode(PTNode::BREAK, yylloc.first_line);
            (yyval.pt) = new PTNode(PTNode::BREAK_STMT,
                std::vector<PTNode*> { tBREAK }, yylloc.first_line);
        }
#line 2456 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"
    break;


#line 2460 "/home/supa/lin_storage/CSE423/frontend/flex_bison/parser.tab.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 750 "frontend/flex_bison/parser.ypp"


/**
 * @brief Error function called if one is encountered during parsing
 *
 * @param s Error string
 */
void yyerror(const char *s)
{
	spdlog::error("{} on line {}", s, yylloc.first_line);
	exit(-1);
}
