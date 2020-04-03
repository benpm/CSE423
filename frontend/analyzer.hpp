/**
 * @file analyzer.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header for SemanticAnalyzer subsystem
 * @date 2020-03-07
 *
 */
#pragma once

#include <utility>
#include <vector>
#include <ast.hpp>
#include <symboltable.hpp>

/**
 * @brief Data structure to represent a compiler warning
 *
 */
struct Error {
    enum Category {
        UnusedVariable, UnusedFunction, UnusedLabel, // Warnings
        UndeclaredVariable, MainUndefined, VariableRedclaration, UninitializedVariableUse // Errors
    };

    Category category;
    uint lineNumber;
    std::string varName;

    bool isFatal;   // (non-fatal) warning or (fatal) error?
    std::string messageTemplate;

    void printMessage();

    Error(Category cat, uint lineno, std::string name);
    Error(Category cat, uint lineno) : Error(cat, lineno, "") {};
};

/**
 * @brief Class for semantic analyzer subsystem
 *
 */
class SemanticAnalyzer {
private:
    AST &ast;
    SymbolTable &table;
    std::vector<Error> errors;

    void analyzeProgram();

public:
    bool hasWarning = false;
    bool hasError = false;

    void printErrors();

    SemanticAnalyzer(AST &ast, SymbolTable &st);
};
