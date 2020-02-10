snazzle.y
%{
	#include <cstdio>
	#include <iostream>

	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;

	void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  Initially (by default), yystype
// is merely a typedef of "int", but for non-trivial projects, tokens could
// be of any arbitrary data type.  So, to deal with that, the idea is to
// override yystype's default typedef to be a C union instead.  Unions can
// hold all of the types of tokens that Flex could return, and this this means
// we can return ints or floats or strings cleanly.  Bison implements this
// mechanism with the %union directive:
%union {
	int ival;
	float fval;
	char *sval;
}

// Define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the %union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%
// This is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:
snazzle:
	INT snazzle      {
		std::cout << "bison found an int: " << $1 << std::endl;
	}
	| FLOAT snazzle  {
		std::cout << "bison found a float: " << $1 << std::endl;
	}
	| STRING snazzle {
		std::cout << "bison found a string: " << $1 << std::endl; free($1);
	}
	| INT            {
		std::cout << "bison found an int: " << $1 << std::endl;
	}
	| FLOAT          {
		std::cout << "bison found a float: " << $1 << std::endl;
	}
	| STRING         {
		std::cout << "bison found a string: " << $1 << std::endl; free($1);
	}
	;
%%

int main(int, char**) {
	// Open a file handle to a particular file:
	FILE *myfile = fopen("a.snazzle.file", "r");
	// Make sure it is valid:
	if (!myfile) {
		std::cout << "I can't open a.snazzle.file!" << std::endl;
		return -1;
	}
	// Set Flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// Parse through the input:
	yyparse();
}

void yyerror(const char *s) {
	std::cout << "EEK, parse error!  Message: " << s << std::endl;
	// might as well halt now:
	exit(-1);
}