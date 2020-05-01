/**
 * @file analyzer.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of SemanticAnalyzer
 * @date 2020-03-07
 *
 */
#include <algorithm>
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
        {Category::UnusedVariable, "line {}: unused variable ‘{}’"},
        {Category::UnusedFunction, "line {}: unused function ‘{}’"},
        {Category::UnusedParam, "line {}: unused function parameter ‘{}’"},
        {Category::UndeclaredVariable, "line {}: attempt to use undeclared variable ‘{}’"},
        {Category::UndefinedLabel, "line {}: attempt to use undefined label ‘{}’"},
        {Category::ShadowedVariable, "line {}: declaration shadows earlier declaration of ‘{}’"},
        {Category::ImproperUse, "line {}: improper use of symbol ‘{}’"},
        {Category::WrongArgCount, "line {}: wrong number of arguments given to function ‘{}’"},
        {Category::Redeclaration, "line {}: redeclaration of symbol ‘{}’"},
        {Category::UninitializedVariable, "line {}: attempt to use uninitialized variable ‘{}’"}
    };

    this->category = cat;
    this->lineNumber = lineno;
    this->varName = name;
    this->messageTemplate = templateMap.at(cat);

    switch (cat) {
        case Category::UnusedVariable:
        case Category::UnusedFunction:
        case Category::UnusedParam:
        case Category::UninitializedVariable:
        case Category::ShadowedVariable:
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
    if (isFatal)
        spdlog::error(messageTemplate, lineNumber, varName);
    else
        spdlog::warn(messageTemplate, lineNumber, varName);
}

/**
 * Construct a new SemanticAnalyzer to analyze the given program
 *
 */
SemanticAnalyzer::SemanticAnalyzer(AST &ast)
{
    analyzeProgram(ast);

    // Sort errors by line number
    std::sort(errors.begin(), errors.end(), errorComp);

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
    for (AST *child : ast.children[0]->children) {
        switch (child->label) {
            case AST::Label::declaration:
                // Traverse declaration AST
                analyzeDeclaration(child, globalDeclarations, std::set<std::string>());
                break;
            case AST::Label::function:
                // Traverse function AST
                analyzeFunction(child, globalDeclarations);
        }
    }

    for (auto var : ast.children[0]->inScope->table) {
        if (var.first == "main")
            continue;
        if (!isUsed(ast.children[0]->inScope->getSymbol(var.first.c_str()))) {
            uint line = symbolLineNumber[ast.children[0]->inScope->getSymbol(var.first.c_str())];
            switch (var.second.category) {
                case Symbol::Category::Function:
                    errors.emplace_back(Error::Category::UnusedFunction, line, var.first);
                    break;
                case Symbol::Category::Local:
                    errors.emplace_back(Error::Category::UnusedVariable, line, var.first);
            }
        }
    }
}

/**
 * Analyze a function AST
 *
 * @param func The AST subtree node to traverse (must be a function)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeFunction(AST const *func, std::set<std::string> &parentDecls)
{
    std::set<std::string> localDecls;

    std::string symbolName = func->children[1]->data.sval;
    if (isDeclared(symbolName, parentDecls)) {
        // Error: symbol being redeclared
        errors.emplace_back(Error::Category::Redeclaration, func->children[1]->lineNum,
                            symbolName);
    } else {
        parentDecls.insert(symbolName);
        symbolLineNumber[func->ownsScope->getSymbol(symbolName.c_str())] =
            func->lineNum;
    }

    functionParamCount[symbolName] = func->children[2]->children.size() / 2;
    for (AST const *param : func->children[2]->children) {
        if (param->label == AST::Label::id) {
            std::string paramName = param->data.sval;
            localDecls.insert(paramName);
            initialized.insert(param->inScope->getSymbol(paramName.c_str()));
        }
    }

    for (AST const *decl : func->children[3]->children)
        analyzeDeclaration(decl, localDecls, parentDecls);

    localDecls.insert(parentDecls.begin(), parentDecls.end());
    for (AST const *stmt : func->children[4]->children)
        analyzeTerm(stmt, localDecls);

    // Check for unused variables
    for (auto var : func->ownsScope->table) {
        if (!isUsed(func->ownsScope->getSymbol(var.first.c_str()))) {
            uint line = symbolLineNumber[func->ownsScope->getSymbol(var.first.c_str())];
            switch (var.second.category) {
                case Symbol::Category::Parameter:
                    errors.emplace_back(Error::Category::UnusedParam, line, var.first);
                    break;
                case Symbol::Category::Local:
                    errors.emplace_back(Error::Category::UnusedVariable, line, var.first);
            }
        }
    }
}

/**
 * Analyze a declaration AST
 *
 * @param decl The AST subtree node to traverse (must be a declaration)
 * @param parentDecls A mutable reference to the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeDeclaration(AST const *decl, std::set<std::string> &localDecls,
                                          std::set<std::string> const &parentDecls)
{
    std::set<std::string> liveDecls;

    if (decl->children[1]->label == AST::Label::assignment) {
        // Get name of identifier
        std::string symbolName = decl->children[1]->children[0]->data.sval;
        if (isDeclared(symbolName, localDecls)) {
            // Error: symbol being redeclared
            errors.emplace_back(Error::Category::Redeclaration, decl->lineNum, symbolName);
        } else {
            localDecls.insert(symbolName);
            symbolLineNumber[decl->inScope->getSymbol(symbolName.c_str())] =
                decl->children[1]->children[0]->lineNum;
        }

        if (isDeclared(symbolName, parentDecls)) {
            // Warning: symbol being shadowed
            errors.emplace_back(Error::Category::ShadowedVariable, decl->lineNum, symbolName);
        }

        liveDecls.insert(localDecls.begin(), localDecls.end());
        liveDecls.insert(parentDecls.begin(), parentDecls.end());
        // Analyze rvalue of assignment operator
        analyzeOperation(decl->children[1], liveDecls);
    } else {
        // Get name of identifier
        std::string symbolName = decl->children[1]->data.sval;
        if (isDeclared(symbolName, localDecls)) {
            // Error: symbol being redeclared
            errors.emplace_back(Error::Category::Redeclaration, decl->lineNum, symbolName);
        } else {
            localDecls.insert(symbolName);
            symbolLineNumber[decl->inScope->getSymbol(symbolName.c_str())] =
                decl->children[1]->lineNum;
        }

        if (isDeclared(symbolName, parentDecls)) {
            // Warning: symbol being shadowed
            errors.emplace_back(Error::Category::ShadowedVariable, decl->lineNum, symbolName);
        }
    }
}

/**
 * Analyze an operation AST
 *
 * @param op The AST subtree node to traverse (must be an operation)
 * @param parentDecls A reference to the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeOperation(AST const *op, std::set<std::string> const &parentDecls)
{
    switch (op->label) {
        case AST::Label::assignment: {
            // assignment operation
            // Symbol is being initialized
            std::string symbolName = op->children[0]->data.sval;
            initialized.insert(op->inScope->getSymbol(symbolName.c_str()));
            // analyze RHS
            analyzeTerm(op->children[1], parentDecls);
            break; }
        case AST::Label::incr:
        case AST::Label::decr:
        case AST::Label::unary_minus:
        case AST::Label::log_not:
        case AST::Label::return_stmt:
            // unary operation
            analyzeTerm(op->children[0], parentDecls);
            break;
        default:
            // binary operation
            // analyze LHS
            analyzeTerm(op->children[0], parentDecls);
            // analyze RHS
            analyzeTerm(op->children[1], parentDecls);
    }
}

/**
 * Analyze a term, discerning whether it is an identifier, call, constant, or operation
 * 
 * @param term The AST subtree node to traverse (must be one of the above)
 * @param parentDecls A reference to the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeTerm(AST const *term, std::set<std::string> const &parentDecls)
{
    switch (term->label) {
        case AST::Label::id: {
            std::string symbolName = term->data.sval;
            if (!isDeclared(symbolName, parentDecls)) {
                // Error: variable not declared
                errors.emplace_back(Error::Category::UndeclaredVariable,
                                    term->lineNum, symbolName);
            } else if (term->inScope->getSymbol(symbolName.c_str())->category
                    != Symbol::Category::Local
                    && term->inScope->getSymbol(symbolName.c_str())->category
                    != Symbol::Category::Parameter) {
                // Error: improper use of function as variable
                errors.emplace_back(Error::Category::ImproperUse,
                                    term->lineNum, symbolName);
            } else if (!isInitialized(term->inScope->getSymbol(symbolName.c_str()))) {
                // Warning: variable not initialized
                errors.emplace_back(Error::Category::UninitializedVariable,
                                    term->lineNum, symbolName);
            }
            // Mark symbol as used
            if (isDeclared(symbolName, parentDecls))
                used.insert(term->inScope->getSymbol(symbolName.c_str()));
            break; }
        case AST::Label::call:
            analyzeCall(term, parentDecls);
            break;
        case AST::Label::int_const:
        case AST::Label::float_const:
        case AST::Label::char_const:
            // ignore constants
            break;
        case AST::Label::if_stmt:
        case AST::Label::else_if:
        case AST::Label::else_stmt:
            analyzeIfElse(term, parentDecls);
            break;
        case AST::Label::for_stmt:
            analyzeFor(term, parentDecls);
            break;
        case AST::Label::while_stmt:
            analyzeWhile(term, parentDecls);
            break;
        case AST::Label::label_stmt:
            break;
        case AST::Label::goto_stmt:
            analyzeGoto(term, parentDecls);
            break;
        case AST::Label::break_stmt:
            // ignore breaks
            break;
        default:
            // must be operation
            analyzeOperation(term, parentDecls);
    }
}

/**
 * Analyze a function call AST
 *
 * @param call The AST subtree node to traverse (must be a function call)
 * @param parentDecls A reference to the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeCall(AST const *call, std::set<std::string> const &parentDecls)
{
    std::string symbolName = call->children[0]->data.sval;

    if (isDeclared(symbolName, parentDecls)
            && call->inScope->getSymbol(symbolName.c_str())->category
            != Symbol::Category::Function) {
        // Error: cannot call variable as function
        errors.emplace_back(Error::Category::ImproperUse, call->lineNum, symbolName);
    }


    // Mark symbol as used
    if (isDeclared(symbolName, parentDecls))
        used.insert(call->inScope->getSymbol(symbolName.c_str()));

    if (call->children.size() > 1) {
        if (isDeclared(symbolName, parentDecls) && call->children[1]->children.size()
                != functionParamCount[symbolName]) {
            // Error: incorrect number of parameters
            errors.emplace_back(Error::Category::WrongArgCount, call->lineNum, symbolName);
        }
        for (AST *arg : call->children[1]->children) {
            switch (arg->label) {
                case AST::Label::id: {
                    std::string argName = arg->data.sval;
                    if (!isDeclared(argName, parentDecls)) {
                        // Error: variable not declared
                        errors.emplace_back(Error::Category::UndeclaredVariable,
                                            arg->lineNum, argName);
                    } else if (!isInitialized(arg->inScope->getSymbol(argName.c_str()))) {
                        // Warning: variable not initialized
                        errors.emplace_back(Error::Category::UninitializedVariable,
                                            arg->lineNum, argName);
                    }
                    if (isDeclared(argName, parentDecls))
                        used.insert(call->inScope->getSymbol(argName.c_str()));
                    break; }
                case AST::Label::call:
                    analyzeCall(arg, parentDecls);
                    break;
                case AST::Label::int_const:
                case AST::Label::float_const:
                case AST::Label::char_const:
                case AST::Label::string_const:
                    // ignore constants
                    break;
                default:
                    // must be operation
                    analyzeOperation(arg, parentDecls);
            }
        }
    }
}

/**
 * Analyze a if-else AST
 *
 * @param ifElse The AST subtree node to traverse (must be a for-loop)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeIfElse(AST const *ifElse, std::set<std::string> const &parentDecls)
{
    std::set<std::string> localDecls;

    switch (ifElse->label) {
        case AST::Label::if_stmt:
            analyzeTerm(ifElse->children[0], parentDecls);
            for (AST const *decl : ifElse->children[1]->children)
                analyzeDeclaration(decl, localDecls, parentDecls);

            localDecls.insert(parentDecls.begin(), parentDecls.end());
            for (AST const *stmt : ifElse->children[2]->children)
                analyzeTerm(stmt, parentDecls);
            
            for (auto it = ifElse->children.begin() + 3; it < ifElse->children.end(); it++)
                analyzeIfElse(*it, parentDecls);
            break;
        case AST::Label::else_if:
            analyzeTerm(ifElse->children[0], parentDecls);
            for (AST const *decl : ifElse->children[1]->children)
                analyzeDeclaration(decl, localDecls, parentDecls);

            localDecls.insert(parentDecls.begin(), parentDecls.end());
            for (AST const *stmt : ifElse->children[2]->children)
                analyzeTerm(stmt, parentDecls);
            break;
        case AST::Label::else_stmt:
            for (AST const *decl : ifElse->children[0]->children)
                analyzeDeclaration(decl, localDecls, parentDecls);

            localDecls.insert(parentDecls.begin(), parentDecls.end());
            for (AST const *stmt : ifElse->children[1]->children)
                analyzeTerm(stmt, localDecls);
    }

    // Check for unused variables
    for (auto var : ifElse->ownsScope->table) {
        if (!isUsed(ifElse->ownsScope->getSymbol(var.first.c_str()))) {
            uint line = symbolLineNumber[ifElse->ownsScope->getSymbol(var.first.c_str())];
            switch (var.second.category) {
                case Symbol::Category::Parameter:
                    errors.emplace_back(Error::Category::UnusedParam, line, var.first);
                    break;
                case Symbol::Category::Local:
                    errors.emplace_back(Error::Category::UnusedVariable, line, var.first);
            }
        }
    }
}

/**
 * Analyze a for-loop AST
 *
 * @param forLoop The AST subtree node to traverse (must be a for-loop)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeFor(AST const *forLoop, std::set<std::string> const &parentDecls)
{
    std::set<std::string> localDecls;
    std::set<std::string> liveDecls;

    analyzeDeclaration(forLoop->children[0], localDecls, parentDecls);
    liveDecls.insert(localDecls.begin(), localDecls.end());
    liveDecls.insert(parentDecls.begin(), parentDecls.end());
    analyzeTerm(forLoop->children[1], liveDecls);
    analyzeTerm(forLoop->children[2], liveDecls);

    for (AST const *decl : forLoop->children[3]->children)
        analyzeDeclaration(decl, localDecls, parentDecls);

    localDecls.insert(parentDecls.begin(), parentDecls.end());
    for (AST const *stmt : forLoop->children[4]->children)
        analyzeTerm(stmt, localDecls);

    // Check for unused variables
    for (auto var : forLoop->ownsScope->table) {
        if (!isUsed(forLoop->ownsScope->getSymbol(var.first.c_str()))) {
            uint line = symbolLineNumber[forLoop->ownsScope->getSymbol(var.first.c_str())];
            switch (var.second.category) {
                case Symbol::Category::Parameter:
                    errors.emplace_back(Error::Category::UnusedParam, line, var.first);
                    break;
                case Symbol::Category::Local:
                    errors.emplace_back(Error::Category::UnusedVariable, line, var.first);
            }
        }
    }
}

/**
 * Analyze a while-loop AST
 *
 * @param whileLoop The AST subtree node to traverse (must be a while-loop)
 * @param parentDecls A mutable copy of the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeWhile(AST const *whileLoop, std::set<std::string> const &parentDecls)
{
    std::set<std::string> localDecls;

    analyzeTerm(whileLoop->children[0], parentDecls);
    for (AST const *decl : whileLoop->children[1]->children)
        analyzeDeclaration(decl, localDecls, parentDecls);

    localDecls.insert(parentDecls.begin(), parentDecls.end());
    for (AST const *stmt : whileLoop->children[2]->children)
        analyzeTerm(stmt, localDecls);

    // Check for unused variables
    for (auto var : whileLoop->ownsScope->table) {
        if (!isUsed(whileLoop->ownsScope->getSymbol(var.first.c_str()))) {
            uint line = symbolLineNumber[whileLoop->ownsScope->getSymbol(var.first.c_str())];
            switch (var.second.category) {
                case Symbol::Category::Parameter:
                    errors.emplace_back(Error::Category::UnusedParam, line, var.first);
                    break;
                case Symbol::Category::Local:
                    errors.emplace_back(Error::Category::UnusedVariable, line, var.first);
            }
        }
    }
}

/**
 * Analyze a goto statement AST
 *
 * @param gotoStmt The AST subtree node to traverse (must be a goto statement)
 * @param parentDecls A reference to the parent scope declarations
 *
 */
void SemanticAnalyzer::analyzeGoto(AST const *gotoStmt, std::set<std::string> const &parentDecls)
{
    std::string labelName = gotoStmt->children[0]->data.sval;
    Symbol *label = gotoStmt->inScope->getSymbol(labelName.c_str());
    if (!label || label->category != Symbol::Category::Label) {
        errors.emplace_back(Error::Category::UndefinedLabel, gotoStmt->children[0]->lineNum,
                            labelName);
    }
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

/**
 * Compare two errors by line number (used for sorting)
 *
 * @param a The first error to compare
 * @param b The second error to compare
 *
 * @return true if error a occurs before b
 */
bool SemanticAnalyzer::errorComp(Error a, Error b)
{
    return bool(a.lineNumber < b.lineNumber);
}

/**
 * Pretty-preint the program warnings and errors
 */
void SemanticAnalyzer::printErrors()
{
    for (Error err : errors)
        err.printMessage();
}
