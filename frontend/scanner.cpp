/**
 * @file scanner.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Simple driver for scanner. Takes in filename as argv[1] and prints all tokens
 * @date 2020-02-11
 * 
 */
#include <iostream>

extern int yylex();
extern FILE *yyin;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " FILE_TO_SCAN" << std::endl;
        return -1;
    }

    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        return -2;
    }

    yyin = myfile;
    while (yylex());
}