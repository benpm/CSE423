/**
 * @file symboltable.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of SymbolTable
 * @date 2020-03-07
 *
 */
#include <iostream>
#include <set>
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <symboltable.hpp>

uint SymbolTable::globalTableID = 0;
std::set<int> SymbolTable::scopeCreators {
    AST::root, AST::for_stmt, AST::if_stmt, AST::else_stmt, AST::else_if, AST::while_stmt,
    AST::function, AST::list
};

/**
 * Construct a new Symbol::Symbol object
 *
 * @param inScopeID scope that the symbol is in (tableID)
 * @param symType type of symbol (int, float, char)
 * @param category category (Function, Local, Parameter, Label)
 *
 */
Symbol::Symbol(uint inScopeID, int symType, Symbol::Category category)
{
    this->inScopeID = inScopeID;
    this->symType = (Symbol::Type)symType;
    this->category = category;
}

/**
 * Construct a new Symbol table from AST
 *
 * @param ast Root node of AST
 *
 */
SymbolTable::SymbolTable(AST* ast)
{
    spdlog::info("Symbol Table population beginning");

    this->tableID = this->globalTableID;
    this->globalTableID++;
    this->name = "__GLOBAL__";

    this->populateChildren(ast);

    spdlog::info("Symbol Table population done");
}

/**
 * Construct a new child symbol table (called internally)
 *
 * @param ast Pointer to AST node that created the new scope
 * @param parent Pointer to the parent (scope) of the current symbol table
 * @param name Name of new table (function name, etc)
 *
 */
SymbolTable::SymbolTable(AST* ast, SymbolTable* parent, std::string name)
{
    this->tableID = this->globalTableID;
    this->globalTableID++;
    this->name = name;
    this->parent = parent;

    this->populateChildren(ast);
}

/**
 * Recursively add symbols to symbol table (and construct new if necessary)
 *
 * @param ast Pointer to root AST node
 *
 */
void SymbolTable::populateChildren(AST* ast)
{
    for (AST* childAST : ast->children) {
        // Really ugly thing for inheriting scope
        if (ast->inScope != NULL && ast->inScope->tableID > this->tableID) {
            childAST->inScope = ast->inScope;
        } else {
            childAST->inScope = this;
        }

        // Functions create symbols and scopes
        if (childAST->label == AST::function) {
            Symbol tmp(this->tableID, childAST->children[0]->label, Symbol::Function);
            this->table.emplace(childAST->children[1]->data.sval, tmp);
        }
        // Scope creators (includes functions) DO NOT RECURSE ON THESE AS THEY CREATE NEW SCOPE
        if (this->scopeCreators.count(childAST->label)) {
            std::string name = childAST->toString();
            if (childAST->label == AST::function)
                name = std::string(childAST->children[1]->data.sval) + "()";

            SymbolTable* parent = NULL;
            if ((childAST->label == AST::else_if) || (childAST->label == AST::else_stmt)) {
                parent = this->parent;
            } else {
                parent = this;
            }

            int insertIndex = parent->children.size();
            SymbolTable* newChild = new SymbolTable(childAST, this, name);
            parent->children.insert(parent->children.begin() + insertIndex, newChild);
            childAST->inScope = parent;
            childAST->ownsScope = newChild;
        }
        // Variable declarations
        if (childAST->label == AST::declaration) {
            AST* symTypeNode = childAST->children[0];
            AST* symNameNode;
            if (childAST->children[1]->label == AST::assignment)
                symNameNode = childAST->children[1]->children[0];
            else
                symNameNode = childAST->children[1];

            Symbol symbol(childAST->inScope->tableID, symTypeNode->label, Symbol::Local);
            childAST->inScope->table.emplace(symNameNode->data.sval, symbol);
        }
        // Function paramaters in declaration
        if (childAST->label == AST::params) {
            for (int i = 0; i < childAST->children.size(); i += 2) {
                AST* symTypeNode = childAST->children[i + 0];
                AST* symNameNode = childAST->children[i + 1];
                Symbol symbol(this->tableID, symTypeNode->label, Symbol::Parameter);
                this->table.emplace(symNameNode->data.sval, symbol);
            }
        }
        // GOTO labels
        if (childAST->label == AST::label_stmt) {
            AST* symNameNode = childAST->children[0];
            Symbol symbol(this->tableID, Symbol::None, Symbol::Label);
            this->table.emplace(symNameNode->data.sval, symbol);
        }
    }

    // Assign correct scope to declarations inside loop bodies
    if (ast->label == AST::for_stmt) {
        ast->children[3]->inScope = ast->children[4]->ownsScope;
    }
    if (ast->label == AST::while_stmt) {
        ast->children[1]->inScope = ast->children[2]->ownsScope;
    }

    for (AST* childAST : ast->children) {
        if (!SymbolTable::scopeCreators.count(childAST->label))
            this->populateChildren(childAST);
    }
}

/**
 * Internal recursive print function
 *
 * @param st Pointer to symbol table to print
 * @param depth Depth of this iteration
 *
 */
void SymbolTable::printTable(SymbolTable* st, uint depth)
{
    // Construct the padding string using bit flags
    std::string padding(depth * 2, ' ');

    // Get longest identifier name
    size_t maxLen = 0;
    for (auto item : st->table)
        maxLen = std::max(item.first.size(), maxLen);
    
    // Create table layout
    fmt::print("{}+----------------------------+\n", padding);
    fmt::print("{}| Table ID: {:<4} {:>11} |\n", padding, st->tableID, st->name);
    fmt::print("{}+----------------------------+\n", padding);
    std::string fmtstr = "{}| {:" + std::to_string(maxLen) + "} | {:6} | {:" +
        std::to_string(14 - maxLen) + "} |\n";

    // Print table entries
    for (auto item : st->table) {
        fmt::print(fmtstr, padding, item.first, 
            std::string(magic_enum::enum_name(item.second.symType)),
            std::string(magic_enum::enum_name(item.second.category))
        );
    }
    if (st->table.empty())
        fmt::print("{}|                            |\n", padding);

    fmt::print("{}+----------------------------+\n", padding);

    // Recurse on the table's children
    for (SymbolTable* child : st->children) {
        printTable(child, depth + 1);
    }
}

/**
 * Print the symbol table
 *
 */
void SymbolTable::print()
{
    printTable(this, 0);
}

/**
 * Get the depth of the symbol table embedded in the scope hierarchy
 *
 * @return the depth of the symbol table
 *
 */
size_t SymbolTable::getDepth()
{
    size_t depth = 0;
    SymbolTable* parent = this->parent;

    while (parent != NULL) {
        parent = parent->parent;
        depth++;
    }

    return depth;
}

Symbol *SymbolTable::getSymbol(const char *name)
{
    SymbolTable* table = this;
    do {
        if (table->table.find(name) != table->table.end())
            return &table->table.at(name);
        table = table->parent;
    } while (table);
    return nullptr;
}

/**
 * @brief Get the Symbol Type of the name, searching up the tree if necessary
 * 
 * @param name The name of symbol
 * @return Symbol::Type The type of the symbol
 */
Symbol::Type SymbolTable::getSymbolType(const char* name)
{
    SymbolTable* table = this;
    do {
        if (table->table.find(name) != table->table.end())
            return table->table.at(name).symType;
        table = table->parent;
    } while (table);
    return Symbol::Type::None;
}