/**
 * @file analyzer.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of SemanticAnalyzer
 * @date 2020-03-07
 *
 */
#include <map>
#include <set>
#include <spdlog/spdlog.h>
#include <analyzer.hpp>
#include <ast.hpp>
#include <symboltable.hpp>

/**
 * Construct a new warning/error data structure
 *
 * @param cat The error category
 * @param lineno The line number of the error
 * @param name The name of the error-causing variable (empty string if not any)
 *
 */
Error::Error(Category cat, uint lineno, std::string name)
{
    const std::map<Category, const std::string> templateMap {
        {Category::UnusedVariable, "line {}: unused variable `{}`"},
        {Category::UnusedFunction, "line {}: unused function `{}`"},
        {Category::UnusedLabel, "line {}: unused label `{}`"},
        {Category::UndeclaredVariable, "line {}: attempt to use undeclared variable `{}`"},
        {Category::MainUndefined, "must define function `main` which returns `int` "
                                  "and has no paramaters"},
        {Category::Redeclaration, "line {}: redeclaration of variable `{}`"},
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
        case Category::UninitializedVariableUse:
            isFatal = false;
            break;
        default:
            isFatal = true;
    }
}

/**
 * Print the error message using spdlog
 *
 */
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

/**
 * Construct a new SemanticAnalyzer to analyze the given program
 *
 */
SemanticAnalyzer::SemanticAnalyzer(AST &ast)
{
    analyzeProgram(ast);

    // Flag errors and warnings
    for (Error error : errors) {
        if (error.isFatal)
            hasError = true;
        else
            hasWarning = true;

        // Break early if no more updates
        if (hasError && hasWarning)
            break;
    }
}

/**
 * Analyze the given program for errors
 *
 * @param ast The program AST
 *
 */
void SemanticAnalyzer::analyzeProgram(AST const &ast)
{
    std::set<std::string> globalDeclarations;
    for (AST *child: ast.children[0]->children) {
        switch (child->label) {
            case AST::Label::declaration:
                // Traverse declaration AST
                analyzeDeclaration(child, globalDeclarations);
                break;
            case AST::Label::function:
                // Traverse function AST
                analyzeFunction(child, globalDeclarations);
                break;
        }
    }
}

/**
 * Analyze a declaration AST
 *
 * @param decl The AST subtree node to traverse (must be a declaration)
 * @param parentDecls A reference to the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeDeclaration(AST const *decl, std::set<std::string> &parentDecls)
{
    if (decl->children[1]->label == AST::Label::assignment) {
        // Get symbol of identifier
        std::string symbolName = decl->children[1]->children[0]->data.sval;
        if (isDeclared(symbolName, parentDecls)) {
            // Error: symbol being redeclared
            errors.emplace_back(Error::Category::Redeclaration, decl->lineNum, symbolName);
        }
        parentDecls.insert(symbolName);
        // Symbol is being initialized
        initialized.insert(&decl->inScope->table.at(symbolName));
        // Analyze rvalue of assignment operator
        analyzeOperation(decl->children[1], parentDecls);
    } else {
        // Get symbol of identifier
        std::string symbolName = decl->children[1]->data.sval;
        if (isDeclared(symbolName, parentDecls)) {
            // Error: symbol being redeclared
            errors.emplace_back(Error::Category::Redeclaration, decl->lineNum, symbolName);
        }
        parentDecls.insert(symbolName);
    }
}

/**
 * Analyze an operation AST
 *
 * @param op The AST subtree node to traverse (must be an operation)
 * @param parentDecls A reference to the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeOperation(AST const *op, std::set<std::string> &parentDecls)
{
    switch (op->children[1]->label) {
        case AST::Label::sum:
        case AST::Label::sub:
        case AST::Label::mul:
        case AST::Label::divide:
        case AST::Label::log_and:
        case AST::Label::log_or:
            break;
        case AST::Label::log_not:
            break;
        case AST::Label::incr:
        case AST::Label::decr:
            break;
        case AST::Label::call:
            break;
        default:
            break;
    }

}

/**
 * Analyze a function AST
 *
 * @param func The AST subtree node to traverse (must be a function)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeFunction(AST const *func, std::set<std::string> parentDecls)
{
    std::set<std::string> localDecls;

}

/**
 * Analyze a if-else AST
 *
 * @param ifElse The AST subtree node to traverse (must be a for-loop)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeIfElse(AST const *ifElse, std::set<std::string> parentDecls)
{
    std::set<std::string> localDecls;
}

/**
 * Analyze a for-loop AST
 *
 * @param forLoop The AST subtree node to traverse (must be a for-loop)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeFor(AST const *forLoop, std::set<std::string> parentDecls)
{
    std::set<std::string> localDecls;
}

/**
 * Analyze a while-loop AST
 *
 * @param whileLoop The AST subtree node to traverse (must be a while-loop)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeWhile(AST const *whileLoop, std::set<std::string> parentDecls)
{
    std::set<std::string> localDecls;
}

/**
 * Determine if a symbol has been declared
 *
 * @param name The symbol identifier
 * @param decls Reference to the declarations list being checked
 *
 * @return true if the symbol is in decls, else false
 *
 */
bool SemanticAnalyzer::isDeclared(std::string name, std::set<std::string> const &decls)
{
    return bool(decls.find(name) != decls.end());
}

/**
 * Determine if a symbol has been initialized
 *
 * @param s The symbol
 *
 * @return true if the symbol has been initialized, else false
 *
 */
bool SemanticAnalyzer::isInitialized(Symbol *s)
{
    return bool(initialized.find(s) != initialized.end());
}

/**
 * Determine if a symbol has been used
 *
 * @param s The symbol
 *
 * @return true if the symbol has been used, else false
 *
 */
bool SemanticAnalyzer::isUsed(Symbol *s)
{
    return bool(used.find(s) != used.end());
}

void SemanticAnalyzer::printErrors()
{
    for (Error err : errors)
        err.printMessage();
}
