/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_HOME_SUPA_DOCUMENTS_CSE423_FRONTEND_FLEX_BISON_PARSER_TAB_HPP_INCLUDED
# define YY_YY_HOME_SUPA_DOCUMENTS_CSE423_FRONTEND_FLEX_BISON_PARSER_TAB_HPP_INCLUDED
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
    PT* pt;

#line 113 "/home/supa/Documents/CSE423/frontend/flex_bison/parser.tab.hpp"

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

#endif /* !YY_YY_HOME_SUPA_DOCUMENTS_CSE423_FRONTEND_FLEX_BISON_PARSER_TAB_HPP_INCLUDED  */
