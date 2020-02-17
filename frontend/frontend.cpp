/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for scanner + parser. Takes in filename as argv[1] and builds parse tree
 * @date 2020-02-11
 * 
 */
#include <cstdio>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>
#include "parsetree.hpp"

extern ParseTree pt;
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);

int main(int argc, char **argv) {
    // Logging configuration
    spdlog::set_default_logger(spdlog::stderr_color_mt("console"));
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[parser][%^%l%$] %v");

    spdlog::info("Frontend begin");

    // Check if user provided file
    if (argc != 2) {
        spdlog::error("No file provided!\nUsage: {} filepath", argv[0]);
        return -1;
    }

    FILE *myfile = fopen(argv[1], "r");
    // Make sure it opened
    if (!(myfile)) {
        spdlog::error("Cannot open {}\nUsage: {} filepath", argv[1], argv[0]);
        return -2;
    }

    // Point FLEX/BISON to it and run
	yyin = myfile;
	yyparse();
    return 0;
}

void yyerror(const char *s) {
	spdlog::error("Parser error: {}", s);
	exit(-1);
}