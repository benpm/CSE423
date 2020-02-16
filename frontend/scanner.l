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
int                     { yylval.sval = strdup(yytext); return INT;        }
float                   { yylval.sval = strdup(yytext); return FLOAT;      }
char                    { yylval.sval = strdup(yytext); return CHAR;       }
for                     { yylval.sval = strdup(yytext); return FOR;        }
while                   { yylval.sval = strdup(yytext); return WHILE;      }
if                      { yylval.sval = strdup(yytext); return IF;         }
else                    { yylval.sval = strdup(yytext); return ELSE;       }
return                  { yylval.sval = strdup(yytext); return RETURN;     }
break                   { yylval.sval = strdup(yytext); return BREAK;      }
;                       { yylval.cval = yytext[0]; return SEMICOLON;       }
,                       { yylval.cval = yytext[0]; return COMMA;           }
\(                      { yylval.cval = yytext[0]; return LPAREN;          }
\)                      { yylval.cval = yytext[0]; return RPAREN;          }
\{                      { yylval.cval = yytext[0]; return LBRACE;          }
\}                      { yylval.cval = yytext[0]; return RBRACE;          }
\[                      { yylval.cval = yytext[0]; return LBRACK;          }
\]                      { yylval.cval = yytext[0]; return RBRACK;          }
=                       { yylval.cval = yytext[0]; return EQUAL;           }
\+                      { yylval.cval = yytext[0]; return PLUS;            }
-                       { yylval.cval = yytext[0]; return MINUS;           }
\*                      { yylval.cval = yytext[0]; return TIMES;           }
\/                      { yylval.cval = yytext[0]; return DIVIDE;          }
%                       { yylval.cval = yytext[0]; return MODULO;          }
\+=                     { yylval.sval = strdup(yytext); return PLUSEQUAL;  }
-=                      { yylval.sval = strdup(yytext); return MINUSEQUAL; }
\*=                     { yylval.sval = strdup(yytext); return TIMESEQUAL; }
\/=                     { yylval.sval = strdup(yytext); return DIVEQUAL;   }
%=                      { yylval.sval = strdup(yytext); return MODEQUAL;   }
\+\+                    { yylval.sval = strdup(yytext); return INCR;       }
--                      { yylval.sval = strdup(yytext); return DECR;       }
\<                      { yylval.cval = yytext[0]; return LT;              }
\>                      { yylval.cval = yytext[0]; return GT;              }
\<=                     { yylval.sval = strdup(yytext); return LE; 	   	   }
\>=                     { yylval.sval = strdup(yytext); return GE;         }
==                      { yylval.sval = strdup(yytext); return ISEQ;       }
!=                      { yylval.sval = strdup(yytext); return NOTEQ;      }
&&                      { yylval.sval = strdup(yytext); return LOGAND;     }
\|\|                    { yylval.sval = strdup(yytext); return LOGOR;      }
!                       { yylval.cval = yytext[0]; return NOT;             }
\"(\\.|[^"\\])*\"       { yylval.sval = strdup(yytext); return STRINGLIT;  }
'.'                     { yylval.cval = yytext[0]; return CHARLIT;         }
[0-9]+                  { yylval.ival = atoi(yytext); return INTCONST;     }
[0-9]+\.[0-9]?          { yylval.fval = atof(yytext); return FLOATCONST;   }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return ID;         }
.                       { yylval.sval = strdup(yytext); return UNKNOWN;    }
%%