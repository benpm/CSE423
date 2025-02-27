/**
 * @file symboltable.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header for SymbolTable data structure
 * @date 2020-03-07
 *
 */
#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <ast.hpp>

/**
 * @brief Data structure to represent a symbol (identifier)
 *
 */
struct Symbol {
    // NOTE: Do not re-order this enum, their order 
    enum Type {
        Int = AST::int_type, Float = AST::float_type, Char = AST::char_type, None = 0
    };

    enum Category {
        Function, Local, Parameter, Label
    };

    // Type of symbol (int, float, char)
    Symbol::Type symType;
    // Category of symbol (function, local, parameter)
    Symbol::Category category;
    // Table-scope identifier of this symbol
    uint inScopeID;

    Symbol(uint inScopeID, int symType, Symbol::Category category);
    Symbol(AST* node);
};

/**
 * @brief Tree of symbol tables that represent the scope of a program
 *
 */
class SymbolTable {
private:
    static uint globalTableID;

    void printTable(SymbolTable* st, uint depth);
public:
    static std::set<int> scopeCreators;
    // Parent of this table (NULL if root)
    SymbolTable* parent = NULL;
    // The ID of this table (root is always 0)
    uint tableID;
    // The actual mapping (table) from symbol names to symbol information
    std::map<std::string, Symbol> table;
    // The children tables, representing nested scopes
    std::vector<SymbolTable*> children;
    // Convenience name, used for pretty-printing
    std::string name;

    SymbolTable(AST* ast, SymbolTable* parent, std::string name);
    SymbolTable(AST* ast);

    void populateChildren(AST* ast);
    void print();
    size_t getDepth();
    Symbol *getSymbol(const char *name);
    Symbol::Type getSymbolType(const char* name);
};
