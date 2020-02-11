/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for scanner + parser. Takes in filename as argv[1] builds parse tree
 * @date 2020-02-11
 * 
 */
#include <cstdio>
#include <iostream>

extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " FILE_TO_PARSE" << std::endl;
        return -1;
    }

    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        return -2;
    }

	yyin = myfile;

	yyparse();
}

void yyerror(const char *s) {
	std::cout << "EEK, parse error!  Message: " << s << std::endl;
	// might as well halt now:
	exit(-1);
}