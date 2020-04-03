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
#include <analyzer.hpp>
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

    // Analyze program for errors
    SemanticAnalyzer analyzer(ast, symbolTable);

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

    // Print errors/warnings if any
    // Exit if error
    if (analyzer.hasError) {
        spdlog::info("Semantic errors/warnings:");
        analyzer.printErrors();
        return -1;
    } else if (analyzer.hasWarning) {
        spdlog::info("Semantic errors/warnings:");
        analyzer.printErrors();
    }

    spdlog::info("Frontend end");

    return 0;
}
