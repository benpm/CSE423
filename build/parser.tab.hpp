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

#ifndef YY_YY_HOME_SUPA_DOCUMENTS_CSE423_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_HOME_SUPA_DOCUMENTS_CSE423_BUILD_PARSER_TAB_HPP_INCLUDED
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
    FOR = 259,
    WHILE = 260,
    IF = 261,
    ELSE = 262,
    RETURN = 263,
    BREAK = 264,
    GOTO = 265,
    SEMICOLON = 266,
    COLON = 267,
    COMMA = 268,
    LPAREN = 269,
    RPAREN = 270,
    LBRACE = 271,
    RBRACE = 272,
    EQUAL = 273,
    PLUS = 274,
    MINUS = 275,
    TIMES = 276,
    DIVIDE = 277,
    MODULO = 278,
    PLUSEQUAL = 279,
    MINUSEQUAL = 280,
    TIMESEQUAL = 281,
    DIVEQUAL = 282,
    MODEQUAL = 283,
    INCR = 284,
    DECR = 285,
    LT = 286,
    GT = 287,
    LE = 288,
    GE = 289,
    ISEQ = 290,
    NOTEQ = 291,
    LOGAND = 292,
    LOGOR = 293,
    NOT = 294,
    STRINGLIT = 295,
    INTCONST = 296,
    ID = 297,
    UNKNOWN = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "src/flex_bison/parser.ypp"

    int ival;
    float fval;
    char *sval;
    char cval;
    PT* pt;

#line 109 "/home/supa/Documents/CSE423/build/parser.tab.hpp"

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

#endif /* !YY_YY_HOME_SUPA_DOCUMENTS_CSE423_BUILD_PARSER_TAB_HPP_INCLUDED  */
