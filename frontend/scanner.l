%{
    #include <spdlog/spdlog.h>
    #include <spdlog/sinks/stdout_color_sinks.h>
    #include <spdlog/fmt/fmt.h>
    #include "flag.hpp"
    #include "parsetree.hpp"
    #include "parser.tab.hpp"  // to get the token types from Bison
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
int {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "INT");
    return INT;
}
float {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "FLOAT");
    return FLOAT;
}
char {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "CHAR");
    return CHAR;
}
for {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "FOR");
    return FOR;
}
while {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "WHILE");
    return WHILE;
}
if {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "IF");
    return IF;
}
else {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "ELSE");
    return ELSE;
}
return {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "RETURN");
    return RETURN;
}
break {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "BREAK");
    return BREAK;
}
; {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "SEMICOLON");
    return SEMICOLON;
}
, {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "COMMA");
    return COMMA;
}
\( {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "LPAREN");
    return LPAREN;
}
\) {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "RPAREN");
    return RPAREN;
}
\{ {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "LBRACE");
    return LBRACE;
}
\} {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "RBRACE");
    return RBRACE;
}
\[ {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "LBRACK");    
    return LBRACK;
}
\] {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "RBRACK");    
    return RBRACK;
}
= {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "EQUAL");    
    return EQUAL;
}
\+ {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "PLUS");    
    return PLUS;
}
- {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "MINUS");    
    return MINUS;
}
\* {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "TIMES");
    return TIMES;
}
\/ {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "DIVIDE");    
    return DIVIDE;
}
% {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "MODULO");    
    return MODULO;
}
\+= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "PLUSEQUAL");    
    return PLUSEQUAL;
}
-= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "MINUSEQUAL");    
    return MINUSEQUAL;
}
\*= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "TIMESEQUAL");    
    return TIMESEQUAL;
}
\/= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "DIVEQUAL");    
    return DIVEQUAL;
}
%= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "MODEQUAL");    
    return MODEQUAL;
}
\+\+ {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "INCR");    
    return INCR;
}
-- {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "DECR");    
    return DECR;
}
\< {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "LT");    
    return LT;
}
\> {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "GT");    
    return GT;
}
\<= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "LE");    
    return LE;
}
\>= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "GE");    
    return GE;
}
== {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "ISEQ");    
    return ISEQ;
}
!= {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "NOTEQ");    
    return NOTEQ;
}
&& {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "LOGAND");    
    return LOGAND;
}
\|\| {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "LOGOR");    
    return LOGOR;
}
! {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "NOT");    
    return NOT;
}
\"(\\.|[^"\\])*\" {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "STRINGLIT");    
    return STRINGLIT;
}
'.' {
    yylval.cval = yytext[0];
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "CHARLIT");    
    return CHARLIT;
}
[0-9]+ {
    yylval.ival = atoi(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "INTCONST");    
    return INTCONST;
}
[0-9]+\.[0-9]? {
    yylval.fval = atof(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "FLOATCONST");    
    return FLOATCONST;}
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "ID");    
    return ID;
}
. {
    yylval.sval = strdup(yytext);
    if (Flag::tokenPrint)
        spdlog::info("<{}, {}>", yytext, "UNKNOWN");    
    return UNKNOWN;
}
%%
