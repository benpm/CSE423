/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for scanner + parser. Takes in filename as argv[1] and builds parse tree
 * @date 2020-02-11
 * 
 */
#include <cstdio>
#include <iostream>
#include "parsetree.hpp"

extern ParseTree pt;
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);

int main(int argc, char **argv) {
    // Check if user provided file
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " FILE_TO_PARSE" << std::endl;
        return -1;
    }

    FILE *myfile = fopen(argv[1], "r");
    // Make sure it opened
    if (!(myfile)) {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        return -2;
    }

    // Point FLEX/BISON to it and run
	yyin = myfile;
	yyparse();
    return 0;
}

void yyerror(const char *s) {
	std::cout << "EEK, parse error!  Message: " << s << std::endl;
	exit(-1);
}