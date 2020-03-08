/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for scanner + parser. Takes in filename as argv[1] and builds parse tree
 * @date 2020-02-11
 *
 */
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>
#include <ast.hpp>
#include <parsetree.hpp>
#include <config.hpp>
#include <symboltable.hpp>

int main(int argc, char **argv)
{
    // Logging configuration
    spdlog::set_default_logger(spdlog::stderr_color_mt("console"));
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[frontend][%^%l%$] %v");

    spdlog::info("Frontend begin");

    // Parse command line options
    Config config(argc, argv);

    PT pt(config.file);
    if (config.printParseTree) {
        spdlog::info("Parse tree:");
        pt.print();
    }

    // Create abstract syntax tree
    AST ast(&pt);
    if (config.printAST) {
        spdlog::info("Parse tree:");
        ast.print();
    }

    // Create symbol table
    SymbolTable symbolTable(&ast);
    if (config.printSymbolTable) {
        spdlog::info("Symbol table:");
        symbolTable.print();
    }

    spdlog::info("Frontend end");

    return 0;
}