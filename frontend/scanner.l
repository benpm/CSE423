%{
	#include <iostream>
	#include <parser.tab.hpp>  // to get the token types from Bison
%}

%option noyywrap
%x C_COMMENT

%%
[ \t\n]
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>\n   { }
<C_COMMENT>.    { }
"//".*
int                     { std::cout << "IntType:    " << yytext << std::endl; }
float                   { std::cout << "FloatType:  " << yytext << std::endl; }
char                    { std::cout << "CharType:   " << yytext << std::endl; }
for                     { std::cout << "For:        " << yytext << std::endl; }
while                   { std::cout << "While:      " << yytext << std::endl; }
if                      { std::cout << "If:         " << yytext << std::endl; }
else                    { std::cout << "Else:       " << yytext << std::endl; }
return                  { std::cout << "return:     " << yytext << std::endl; }
;                       { std::cout << "Semicolon:  " << yytext << std::endl; }
,                       { std::cout << "Comma:      " << yytext << std::endl; }
\(                      { std::cout << "Oparen:     " << yytext << std::endl; }
\)                      { std::cout << "Cparen:     " << yytext << std::endl; }
\{                      { std::cout << "Obrace:     " << yytext << std::endl; }
\}                      { std::cout << "Cbrace:     " << yytext << std::endl; }
\[                      { std::cout << "Obrack:     " << yytext << std::endl; }
\]                      { std::cout << "Cbrack:     " << yytext << std::endl; }
=                       { std::cout << "Equal:      " << yytext << std::endl; }
%                       { std::cout << "Modulo:     " << yytext << std::endl; }
-                       { std::cout << "Minus:      " << yytext << std::endl; }
\+                      { std::cout << "Plus:       " << yytext << std::endl; }
\/                      { std::cout << "Divide:     " << yytext << std::endl; }
\*                      { std::cout << "Times:      " << yytext << std::endl; }
\<                      { std::cout << "Less:       " << yytext << std::endl; }
\>                      { std::cout << "Greater:    " << yytext << std::endl; }
\<=                     { std::cout << "Le:         " << yytext << std::endl; }
\>=                     { std::cout << "Ge:         " << yytext << std::endl; }
==                      { std::cout << "Iseq:       " << yytext << std::endl; }
!=                      { std::cout << "Noteq:      " << yytext << std::endl; }
&&                      { std::cout << "LogAnd:     " << yytext << std::endl; }
\|\|                    { std::cout << "LogOr:      " << yytext << std::endl; }
#define                 { std::cout << "Define:     " << yytext << std::endl; }
\"(\\.|[^"\\])*\"       { std::cout << "StringLit:  " << yytext << std::endl; }
'.'                     { std::cout << "CharLit:    " << yytext << std::endl; }
[0-9]+\.?[0-9]?         { std::cout << "NumberLit:  " << yytext << std::endl; }
[a-zA-Z_][a-zA-Z_\\d]*  { std::cout << "Identifier: " << yytext << std::endl; }
.                       { std::cout << "UNKNOWN:    " << yytext << std::endl; }
%%