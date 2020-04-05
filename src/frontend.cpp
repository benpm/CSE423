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
#include <ir/program.hpp>

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

    // Input from program, not IR
    if (config.inputCSV.empty()) {
        // Create parsetree from program
        PT pt(config.file);

        // Create abstract syntax tree
        AST ast(&pt);
        
        // Create symbol table
        SymbolTable symbolTable(&ast);

        // Create IR program
        Program program(ast);

        if (config.printSymbolTable) {
            spdlog::info("Symbol table:");
            symbolTable.print();
        }
        if (config.printParseTree) {
            spdlog::info("Parse tree:");
            pt.print();
        }
        if (config.printAST) {
            spdlog::info("Abstract syntax tree:");
            ast.print();
        }
        if (!config.outputCSV.empty()) {
            spdlog::info("IR output as CSV to {}", config.outputCSV);
            program.outputToFile(config.outputCSV);
        }
        if (config.printIR) {
            spdlog::info("IR:");
            program.print();
        }
    } else {
        Program program(config.inputCSV);

        if (config.printSymbolTable)
            spdlog::info("IR as input, ignoring symbol table print flag");
        if (config.printParseTree)
            spdlog::info("IR as input, ignoring parsetree print flag");
        if (config.printAST)
            spdlog::info("IR as input, ignoring abstract syntax tree print flag");
        if (!config.outputCSV.empty()) {
            spdlog::info("IR output as CSV to {}", config.outputCSV);
            program.outputToFile(config.outputCSV);
        }
        if (config.printIR) {
            spdlog::info("IR:");
            program.print();
        }
    }

    spdlog::info("Frontend end");

    return 0;
}
