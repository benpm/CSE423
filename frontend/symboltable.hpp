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

    Symbol::Type symType;
    Symbol::Category category;
    uint scopeID;

    Symbol(uint scopeID, Symbol::Type symType, Symbol::Category category);
};

class SymbolTable {
public:
    SymbolTable* parent;
    uint tableID;
    std::unordered_map<std::string, Symbol> table;
    std::vector<SymbolTable*> children;

    SymbolTable(AST* ast, uint tableID);
    void print();
};