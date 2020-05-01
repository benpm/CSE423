/**
 * @file analyzer.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header for SemanticAnalyzer subsystem
 * @date 2020-03-07
 *
 */
#pragma once

#include <map>
#include <set>
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
        UnusedVariable, UnusedFunction, UnusedParam, UninitializedVariable, ShadowedVariable, // Warnings
        UndeclaredVariable, UndefinedLabel, ImproperUse, WrongArgCount, Redeclaration // Errors
    };

    Category category;
    uint lineNumber;
    std::string varName;

    bool isFatal;   // (non-fatal) warning or (fatal) error?
    std::string messageTemplate;

    void printMessage();

    Error(Category cat, uint lineno, std::string name);
};

/**
 * @brief Class for semantic analyzer subsystem
 *
 */
class SemanticAnalyzer {
private:
    std::set<Symbol*> initialized;
    std::set<Symbol*> used;
    std::map<std::string, uint> functionParamCount;
    std::map<Symbol *, uint> symbolLineNumber;
    std::vector<Error> errors;

    void analyzeProgram(AST const &ast);
    void analyzeFunction(AST const *func, std::set<std::string> &parentDecls);
    void analyzeDeclaration(AST const *decl, std::set<std::string> &localDecls,
                            std::set<std::string> const &parentDecls);
    void analyzeOperation(AST const *op, std::set<std::string> const &parentDecls);
    void analyzeTerm(AST const *term, std::set<std::string> const &parentDecls);
    void analyzeCall(AST const *call, std::set<std::string> const &parentDecls);
    void analyzeIfElse(AST const *ifElse, std::set<std::string> const &parentDecls);
    void analyzeFor(AST const *forLoop, std::set<std::string> const &parentDecls);
    void analyzeWhile(AST const *whileLoop, std::set<std::string> const &parentDecls);
    void analyzeGoto(AST const *gotoStmt, std::set<std::string> const &parentDecls);
    bool isDeclared(std::string name, std::set<std::string> const &decls);
    bool isInitialized(Symbol *s);
    bool isUsed(Symbol *s);
    static bool errorComp(Error a, Error b);

public:
    bool hasWarning = false;
    bool hasError = false;

    void printErrors();

    SemanticAnalyzer(AST &ast);
};
