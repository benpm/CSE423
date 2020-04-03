/**
 * @file analyzer.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of SemanticAnalyzer
 * @date 2020-03-07
 *
 */
#include <map>
#include <spdlog/spdlog.h>
#include <analyzer.hpp>
#include <ast.hpp>
#include <symboltable.hpp>

Error::Error(Category cat, uint lineno, std::string name)
{
    const std::map<Category, const std::string> templateMap {
        {Category::UnusedVariable, "line {}: unused variable `{}`"},
        {Category::UnusedFunction, "line {}: unused function `{}`"},
        {Category::UnusedLabel, "line {}: unused label `{}`"},
        {Category::UndeclaredVariable, "line {}: attempt to use undeclared variable `{}`"},
        {Category::MainUndefined, "must define function `main` which returns `int` "
                                  "and has no paramaters"},
        {Category::VariableRedclaration, "line {}: redeclaration of variable `{}`"},
        {Category::UninitializedVariableUse, "line {}: attempt to use uninitialized variable `{}`"}
    };

    this->category = cat;
    this->lineNumber = lineno;
    this->varName = name;
    this->messageTemplate = templateMap.at(cat);

    switch (cat) {
    case Category::UnusedVariable:
    case Category::UnusedFunction:
    case Category::UnusedLabel:
        isFatal = false;
        break;
    default:
        isFatal = true;
    }
}

void Error::printMessage()
{
    if (isFatal) {
        if (category == Category::MainUndefined)
            spdlog::error(messageTemplate);
        else
            spdlog::error(messageTemplate, lineNumber, varName);
    } else {
        spdlog::warn(messageTemplate, lineNumber, varName);
    }
}

SemanticAnalyzer::SemanticAnalyzer(AST &ast, SymbolTable &table)
{
    analyzeProgram(ast, table);
}

void SemanticAnalyzer::analyzeProgram(AST &ast, SymbolTable &table)
{
    // TODO
}

void SemanticAnalyzer::printErrors()
{
    for (Error err : errors)
        err.printMessage();
}
