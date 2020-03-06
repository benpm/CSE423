%{
    #include <cstdio>
    #include <spdlog/spdlog.h>
    #include <spdlog/sinks/stdout_color_sinks.h>
    #include <spdlog/fmt/fmt.h>
    #include <parsetree.hpp>
    #include <parser.tab.hpp>  // to get the token types from Bison
    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

    bool scannerPrintTokens = false;
%}
%option noyywrap
%option yylineno
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
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "INT");
    return INT;
}
float {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "FLOAT");
    return FLOAT;
}
char {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "CHAR");
    return CHAR;
}
for {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "IF");
    return FOR;
}
while {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "WHILE");
    return WHILE;
}
if {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "IF");
    return IF;
}
else {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "ELSE");
    return ELSE;
}
return {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "RETURN");
    return RETURN;
}
break {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "BREAK");
    return BREAK;
}
; {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "SEMICOLON");
    return SEMICOLON;
}
, {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "COMMA");
    return COMMA;
}
\( {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "LPAREN");
    return LPAREN;
}
\) {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "RPAREN");
    return RPAREN;
}
\{ {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "LBRACE");
    return LBRACE;
}
\} {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "RBRACE");
    return RBRACE;
}
\[ {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "LBRACK");
    return LBRACK;
}
\] {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "RBRACK");
    return RBRACK;
}
= {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "EQUAL");
    return EQUAL;
}
\+ {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "PLUS");
    return PLUS;
}
- {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "MINUS");
    return MINUS;
}
\* {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "TIMES");
    return TIMES;
}
\/ {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "DIVIDE");
    return DIVIDE;
}
% {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "MODULO");
    return MODULO;
}
\+= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "PLUSEQUAL");
    return PLUSEQUAL;
}
-= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "MINUSEQUAL");
    return MINUSEQUAL;
}
\*= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "TIMESEQUAL");
    return TIMESEQUAL;
}
\/= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "DIVEQUAL");
    return DIVEQUAL;
}
%= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "MODEQUAL");
    return MODEQUAL;
}
\+\+ {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "INCR");
    return INCR;
}
-- {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "DECR");
    return DECR;
}
\< {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "LT");
    return LT;
}
\> {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "GT");
    return GT;
}
\<= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "LE");
    return LE;
}
\>= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "GE");
    return GE;
}
== {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "ISEQ");
    return ISEQ;
}
!= {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "NOTEQ");
    return NOTEQ;
}
&& {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "LOGAND");
    return LOGAND;
}
\|\| {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "LOGOR");
    return LOGOR;
}
! {
    yylval.cval = yytext[0];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "NOT");
    return NOT;
}
\"(\\.|[^"\\])*\" {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "STRINGLIT");
    return STRINGLIT;
}
'.' {
    yylval.cval = yytext[1];
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "CHARLIT");
    return CHARLIT;
}
[0-9]+ {
    yylval.ival = atoi(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "INTCONST");
    return INTCONST;
}
([0-9]+\.[0-9]*)|([0-9]*\.[0-9]+)  {
    yylval.fval = atof(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "FLOATCONST");
    return FLOATCONST;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "ID");
    return ID;
}
. {
    yylval.sval = strdup(yytext);
    if (scannerPrintTokens)
        printf("<%s, %s>\n", yytext, "UNKNOWN");
    return UNKNOWN;
}
%%
