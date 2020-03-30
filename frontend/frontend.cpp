/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Main frontend entry point for Super Compiler 64
 * @date 2020-02-11
 *
 */
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <ast.hpp>
#include <config.hpp>
#include <parsetree.hpp>
#include <symboltable.hpp>

// Main entry point for compiler
int main(int argc, char **argv)
{
    // Logging configuration
    spdlog::set_default_logger(spdlog::stderr_color_mt("console"));
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[frontend][%^%l%$] %v");

    // Parse command line options
    Config config(argc, argv);

    spdlog::info("Frontend begin");

    // Create parsetree from input file
    PT pt(config.file);

    // Create abstract syntax tree
    AST ast(&pt);

    // Create symbol table
    SymbolTable symbolTable(&ast);


    if (config.printParseTree) {
        spdlog::info("Parse tree:");
        pt.print();
    }

    if (config.printAST) {
        spdlog::info("Parse tree:");
        ast.print();
    }

    if (config.printSymbolTable) {
        spdlog::info("Symbol table:");
        symbolTable.print();
    }

    spdlog::info("Frontend end");

    return 0;
}
