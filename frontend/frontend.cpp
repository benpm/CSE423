/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for scanner + parser. Takes in filename as argv[1] and builds parse tree
 * @date 2020-02-11
 * 
 */
#include <cstring>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>
#include <ast.hpp>
#include <parsetree.hpp>
#include <config.hpp>

extern PTNode* pt;
extern int yyparse();
extern FILE *yyin;

int main(int argc, char **argv) {
    // Logging configuration
    spdlog::set_default_logger(spdlog::stderr_color_mt("console"));
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[frontend][%^%l%$] %v");

    // Parse command line options
    Config config(argc, argv);

    // Try to open file
    FILE *myfile = fopen(config.file.c_str(), "r");
    if (!myfile) {
        spdlog::error("Cannot open {}", argv[1]);
        return -1;
    }

    spdlog::info("Frontend begin");

    // Point FLEX/BISON to file and parse
    spdlog::info("Tokenization/parsing beginning");
	yyin = myfile;
	yyparse();
    spdlog::info("Tokenization/parsing done");

    // Create abstract syntax tree
    spdlog::info("AST construction beginning");
    AST ast(pt);
    spdlog::info("AST construction done");

    // Print parse tree if requested
    if (config.printParseTree) {
        pt->print();
    }
    if (config.printAST) {
        ast.print();
    }

    spdlog::info("Frontend exit");

    return 0;
}