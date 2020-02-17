/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for scanner + parser. Takes in filename as argv[1] and builds parse tree
 * @date 2020-02-11
 * 
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>
#include "flag.hpp"
#include "parsetree.hpp"

extern ParseTree pt;
extern int yyparse();
extern FILE *yyin;

bool Flag::tokenPrint = false;
bool Flag::parserPrint = false;

void yyerror(const char *s);

int main(int argc, char **argv) {
    // Logging configuration
    spdlog::set_default_logger(spdlog::stderr_color_mt("console"));
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[frontend][%^%l%$] %v");

    spdlog::info("Frontend begin");

    if (argc < 2) {
        spdlog::error("No file provided!\nUsage: {} filepath [-h] [-t] [-p]", argv[0]);
        return -1;
    }

    FILE *myfile = fopen(argv[1], "r");
    // Make sure it opened
    if (!(myfile)) {
        spdlog::error("Cannot open {}\nUsage: {} filepath [-h] [-t] [-p]", argv[1], argv[0]);
        return -1;
    }

    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            spdlog::info("Help message\nUsage: {} filepath [-h] [-t] [-p]", argv[0]);
            return 0;
        } else if (!strcmp(argv[i], "-t")) {
            Flag::tokenPrint = true;
            spdlog::info("Token printing enabled");
        } else if (!strcmp(argv[i], "-p")) {
            Flag::parserPrint = true;
            spdlog::info("Parse tree printing enabled");
        } else {
            spdlog::error("Option not recognized: {}\n"
                          "Usage: {} filepath [-h] [-t] [-p]", argv[i], argv[0]);
            return -1;
        }
    }

    // Point FLEX/BISON to it and run
	yyin = myfile;
	yyparse();
    if (Flag::parserPrint)
        pt->print();
    return 0;
}

void yyerror(const char *s) {
	spdlog::error("Parser error: {}", s);
	exit(-1);
}
