%{
    #include <iostream>
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
int                     { yylval.sval = yytext; return INT;              }
float                   { yylval.sval = yytext; return FLOAT;            }
char                    { yylval.sval = yytext; return CHAR;             }
for                     { yylval.sval = yytext; return FOR;              }
while                   { yylval.sval = yytext; return WHILE;            }
if                      { yylval.sval = yytext; return IF;               }
else                    { yylval.sval = yytext; return ELSE;             }
return                  { yylval.sval = yytext; return RETURN;           }
break                   { yylval.sval = yytext; return BREAK;            }
;                       { yylval.cval = yytext[0]; return SEMICOLON;     }
,                       { yylval.cval = yytext[0]; return COMMA;         }
\(                      { yylval.cval = yytext[0]; return LPAREN;        }
\)                      { yylval.cval = yytext[0]; return RPAREN;        }
\{                      { yylval.cval = yytext[0]; return LBRACE;        }
\}                      { yylval.cval = yytext[0]; return RBRACE;        }
\[                      { yylval.cval = yytext[0]; return LBRACK;        }
\]                      { yylval.cval = yytext[0]; return RBRACK;        }
=                       { yylval.cval = yytext[0]; return EQUAL;         }
\+                      { yylval.cval = yytext[0]; return PLUS;          }
-                       { yylval.cval = yytext[0]; return MINUS;         }
\*                      { yylval.cval = yytext[0]; return TIMES;         }
\/                      { yylval.cval = yytext[0]; return DIVIDE;        }
%                       { yylval.cval = yytext[0]; return MODULO;        }
\+=                     { yylval.sval = yytext; return PLUSEQUAL;        }
-=                      { yylval.sval = yytext; return MINUSEQUAL;       }
\*=                     { yylval.sval = yytext; return TIMESEQUAL;       }
\/=                     { yylval.sval = yytext; return DIVEQUAL;         }
%=                      { yylval.sval = yytext; return MODEQUAL;         }
\+\+                    { yylval.sval = yytext; return INCR;             }
--                      { yylval.sval = yytext; return DECR;             }
\<                      { yylval.cval = yytext[0]; return LT;            }
\>                      { yylval.cval = yytext[0]; return GT;            }
\<=                     { yylval.sval = yytext; return LE; 	   	         }
\>=                     { yylval.sval = yytext; return GE;               }
==                      { yylval.sval = yytext; return ISEQ;             }
!=                      { yylval.sval = yytext; return NOTEQ;            }
&&                      { yylval.sval = yytext; return LOGAND;           }
\|\|                    { yylval.sval = yytext; return LOGOR;            }
!                       { yylval.cval = yytext[0]; return NOT;           }
#define                 { yylval.sval = yytext; return DEFINE;           }
\"(\\.|[^"\\])*\"       { yylval.sval = yytext; return STRINGLIT;  	     }
'.'                     { yylval.cval = yytext[0]; return CHARLIT;       }
[0-9]+                  { yylval.ival = atoi(yytext); return INTCONST;   }
[0-9]+\.[0-9]?          { yylval.fval = atof(yytext); return FLOATCONST; }
[a-zA-Z_][a-zA-Z_\\d]*  { yylval.sval = yytext; return ID;               }
.                       { yylval.sval = yytext; return UNKNOWN;          }
%%