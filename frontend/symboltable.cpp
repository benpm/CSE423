#include <symboltable.hpp>
#include <set>
#include <spdlog/fmt/fmt.h>
#include <iostream>

std::unordered_map<int, std::string> enumToString{
    {Symbol::Int, "Int"},
    {Symbol::Float, "Float"},
    {Symbol::Char, "Char"},
    {Symbol::Function, "Function"},
    {Symbol::Local, "Local"},
    {Symbol::Parameter, "Parameter"},
};

std::set<AST::Label> scopeNodes{
    AST::root, AST::function, AST::for_stmt, AST::if_stmt, AST::else_stmt, AST::else_if, AST::while_stmt
};

Symbol::Symbol(uint scopeID, Symbol::Type symType, Symbol::Category category)
{
    this->scopeID = scopeID;
    this->symType = symType;
    this->category = category;
}

uint traverseAST(SymbolTable* table, AST* ast)
{
    uint localIDIncrement = 1;
    for (AST* childAST : ast->children) {
        bool traverse = false;
        childAST->scopeID = table->tableID;

        // if declaration
        switch(childAST->label) {
            case AST::function:{
                Symbol symbol(
                    table->tableID,
                    (Symbol::Type)childAST->children[0]->label,
                    Symbol::Function
                );
                table->table.emplace(childAST->children[1]->data.sval, symbol);
            }
            case AST::root:
            case AST::for_stmt:
            case AST::if_stmt:
            case AST::else_stmt:
            case AST::else_if:
            case AST::while_stmt:{
                SymbolTable* newChild = new SymbolTable(childAST, table->tableID + localIDIncrement);
                newChild->parent = table;
                if (childAST->label == AST::function){
                    newChild->name = std::string(childAST->children[1]->data.sval) + "()";
                } else {
                    newChild->name = childAST->toString();
                }
                table->children.push_back(newChild);
                localIDIncrement += 1;
                childAST->ownedScopeID = newChild->tableID;
                break;}
            case AST::declaration:{
                // dec_list -> declaration -> type
                AST* symTypeNode = childAST->children[0];
                // dec_list -> declaration -> assignment -> id
                AST* symNameNode = childAST->children[1]->children[0];

                Symbol symbol(
                    table->tableID,
                    (Symbol::Type)symTypeNode->label,
                    Symbol::Local
                );
                table->table.emplace(
                    symNameNode->data.sval, symbol
                );
                break;}
            case AST::params:{
                for (int i = 0; i < childAST->children.size(); i += 2) {
                    AST* symTypeNode = childAST->children[i + 0];
                    AST* symNameNode = childAST->children[i + 1];

                    Symbol symbol(
                        table->tableID,
                        (Symbol::Type)symTypeNode->label, 
                        Symbol::Parameter
                    );
                    table->table.emplace(
                        symNameNode->data.sval, symbol
                    );
                }
                break;}

            default:
                localIDIncrement = traverseAST(table, childAST);
                break;
        }
    }

    return localIDIncrement;
}

SymbolTable::SymbolTable(AST* ast)
{
    this->tableID = 0;
    this->name = "_GLOBAL_";

    traverseAST(this, ast);
}

SymbolTable::SymbolTable(AST* ast, uint tableID)
{
    this->tableID = tableID;

    traverseAST(this, ast);
}

void stprint(SymbolTable* st, uint depth)
{
    // Do not print empty tables
    if (st->table.size() == 0) return;

    // Construct the padding string using bit flags
    std::string padding;
    for (int i = 0; i < depth; ++i) {
        padding += "  ";
    }

    // Get longest identifier name
    size_t maxLen = 0;
    for (auto item : st->table) {
        maxLen = std::max(item.first.size(), maxLen);
    }
    
    // Create table layout
    fmt::print("{}+----------------------------+\n", padding);
    fmt::print("{}| Table ID: {:<4} {:>11} |\n", padding, st->tableID, st->name);
    fmt::print("{}+----------------------------+\n", padding);
    std::string fmtstr = 
        "{}| {:" + std::to_string(maxLen) + "} | {:6} | {:" + std::to_string(14 - maxLen) + "} |";

    // Print table entries
    for (auto item : st->table) {
        fmt::print(fmtstr, padding, item.first, 
            enumToString.at(item.second.symType), 
            enumToString.at(item.second.category));
        fmt::print("\n");
    }
    fmt::print("{}+----------------------------+\n", padding);

    // Recurse on the table's children
    for (SymbolTable* child : st->children) {
        stprint(child, depth + 1);
    }
}

void SymbolTable::print()
{
    stprint(this, 0);
}