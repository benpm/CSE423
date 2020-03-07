#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <ast.hpp>

class Symbol {
public:
    enum Type {
        Int = AST::int_type, Float = AST::float_type, Char = AST::char_type
    };

    enum Category {
        Function, Local, Parameter
    };

    // Type of symbol (int, float, char)
    Symbol::Type symType;
    // Category of symbol (function, local, parameter)
    Symbol::Category category;
    // Table-scope identifier of this symbol
    uint scopeID;

    Symbol(uint scopeID, Symbol::Type symType, Symbol::Category category);
};

class SymbolTable {
public:
    // Parent of this table (NULL if root)
    SymbolTable* parent;
    // The ID of this table (root is always 0)
    uint tableID;
    // The actual mapping (table) from symbol names to symbol information
    std::unordered_map<std::string, Symbol> table;
    // The children tables, representing nested scopes
    std::vector<SymbolTable*> children;
    // Convenience name, used for pretty-printing
    std::string name;

    SymbolTable(AST* ast);
    SymbolTable(AST* ast, uint tableID);
    void print();
};