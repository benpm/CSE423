#include <symboltable.hpp>
#include <set>
#include <spdlog/fmt/fmt.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <magic_enum.hpp>

uint SymbolTable::globalTableID = 0;
std::set<int> SymbolTable::scopeCreators{AST::root, AST::for_stmt, AST::if_stmt, AST::else_stmt, AST::else_if, AST::while_stmt, AST::function};

/**
 * @brief Construct a new Symbol::Symbol object
 * 
 * @param scopeID scope that the symbol is in (tableID)
 * @param symType type of symbol (int, float, char)
 * @param category category (Function, Local, Parameter, Label)
 */
Symbol::Symbol(uint scopeID, int symType, Symbol::Category category)
{
    this->scopeID = scopeID;
    this->symType = (Symbol::Type)symType;
    this->category = category;
}

/**
 * @brief Construct a new Symbol table from AST
 * 
 * @param ast Root node of AST
 */
SymbolTable::SymbolTable(AST* ast)
{
    this->tableID = this->globalTableID;
    this->globalTableID++;
    this->name = "__GLOBAL__";

    this->populateChildren(ast);
}

/**
 * @brief Construct a new child symbol table (called internally)
 * 
 * @param ast AST node that created the new scope
 * @param name Name of new table (function name, etc)
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
 * @brief Add symbols to symbol table (and construct new if necessary)
 * 
 * @param ast 
 */
void SymbolTable::populateChildren(AST* ast)
{
    for (AST* childAST : ast->children) {
        childAST->scopeID = this->tableID;

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
        
            SymbolTable* newChild = new SymbolTable(childAST, this, name);
            if ((childAST->label == AST::else_if) || (childAST->label == AST::else_stmt)) {
                this->parent->children.push_back(newChild);
                childAST->scopeID = this->parent->tableID;
            } else {
                this->children.push_back(newChild);
            }

            childAST->ownedScopeID = newChild->tableID;
            continue;
        }
        // Variable declarations
        if (childAST->label == AST::declaration) {
            AST* symTypeNode = childAST->children[0];
            AST* symNameNode;
            if (childAST->children[1]->label == AST::assignment)
                symNameNode = childAST->children[1]->children[0];
            else
                symNameNode = childAST->children[1];

            Symbol symbol(this->tableID, symTypeNode->label, Symbol::Local);
            this->table.emplace(symNameNode->data.sval, symbol);
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
            Symbol symbol(this->tableID, Symbol::NoneType, Symbol::Label);
            this->table.emplace(symNameNode->data.sval, symbol);
        }

        this->populateChildren(childAST);
    }
}

/**
 * @brief Internal recursive print function
 * 
 * @param st Symbol table to print
 * @param depth Depth of this iteration
 */
void stprint(SymbolTable* st, uint depth)
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
    std::string fmtstr = "{}| {:" + std::to_string(maxLen) + "} | {:6} | {:" + std::to_string(14 - maxLen) + "} |\n";

    // Print table entries
    for (auto item : st->table) {
        fmt::print(fmtstr, padding, item.first, 
            std::string(magic_enum::enum_name(item.second.symType)), 
            std::string(magic_enum::enum_name(item.second.category))
        );
    }
    fmt::print("{}+----------------------------+\n", padding);

    // Recurse on the table's children
    for (SymbolTable* child : st->children) {
        stprint(child, depth + 1);
    }
}

/**
 * @brief Print this symbol table
 */
void SymbolTable::print()
{
    stprint(this, 0);
}
