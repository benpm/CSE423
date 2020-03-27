#include <symboltable.hpp>
#include <set>
#include <spdlog/fmt/fmt.h>
#include <iostream>
#include <spdlog/spdlog.h>

// Mapping from symbol types/categories to strings
std::unordered_map<int, std::string> enumToString{
    // Types
    {Symbol::Int, "Int"},
    {Symbol::Float, "Float"},
    {Symbol::Char, "Char"},
    // Categories
    {Symbol::Function, "Function"},
    {Symbol::Local, "Local"},
    {Symbol::Parameter, "Parameter"},
};

/**
 * @brief Construct a new Symbol with given scope, type and category
 * 
 * @param scopeID scope identifier number
 * @param symType type for this symbol (int, float, char)
 * @param category category for this symbol (function, local, parameter)
 */
Symbol::Symbol(uint scopeID, Symbol::Type symType, Symbol::Category category)
{
    this->scopeID = scopeID;
    this->symType = symType;
    this->category = category;
}

/**
 * @brief Recursive function that traverses an AST building a symbol table in the process
 * 
 * @param table The symbol table to continue building upon
 * @param ast The AST to pull scope and symbol information from, also populates scope field for nodes
 * @return uint The current table ID to be incremented in further calls
 */
uint traverseAST(SymbolTable* table, AST* ast)
{
    uint localIDIncrement = 1;
    for (AST* childAST : ast->children) {
        bool traverse = false;
        childAST->scope = table;

        switch(childAST->label) {
            // Node is a function, so we add to table and fallthrough to create scope
            case AST::function:{
                Symbol symbol(
                    table->tableID,
                    (Symbol::Type)childAST->children[0]->label,
                    Symbol::Function
                );
                table->table.emplace(childAST->children[1]->data.sval, symbol);
            }

            // These nodes only create new scopes, they are not added to table
            case AST::root:
            case AST::for_stmt:
            case AST::if_stmt:
            case AST::else_stmt:
            case AST::else_if:
            case AST::while_stmt:{
                uint newTableID = table->tableID + localIDIncrement;
                std::string newTableName;
                if (childAST->label == AST::function){
                    newTableName = std::string(childAST->children[1]->data.sval) + "()";
                } else {
                    newTableName = fmt::format("{}0x{:X}", 
                        table->name.substr(0, table->name.find(')') + 1),
                        newTableID);
                }
                SymbolTable* newChild = new SymbolTable(table, childAST, newTableID, newTableName);
                table->children.push_back(newChild);
                localIDIncrement += 1;
                childAST->ownedScope = newChild;
                break;}
            
            // Variable declaration add to table
            case AST::declaration:{
                // dec_list -> declaration -> type
                AST* symTypeNode = childAST->children[0];
                // dec_list -> declaration -> assignment -> id
                AST* symNameNode;
                if (childAST->children[1]->label == AST::assignment)
                    symNameNode = childAST->children[1]->children[0];
                else
                    symNameNode = childAST->children[1];

                Symbol symbol(
                    table->tableID,
                    (Symbol::Type)symTypeNode->label,
                    Symbol::Local
                );
                table->table.emplace(
                    symNameNode->data.sval, symbol
                );
                traverseAST(table, childAST);
                break;}
            
            // Add parameters to table
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
                traverseAST(table, childAST);
                break;}

            // Skip this node, it doesn't matter (recurse)
            default:
                localIDIncrement = traverseAST(table, childAST);
                break;
        }
    }

    // Return id so we can continue incrementing for new scopes
    return localIDIncrement + 1;
}

/**
 * @brief Construct a new Symbol Table from given AST (also updates AST nodes with scope IDs)
 * 
 * @param ast The AST to build the table from
 */
SymbolTable::SymbolTable(AST* ast)
{
    spdlog::info("Symbol Table population beginning");

    this->tableID = 0;
    this->name = "_GLOBAL_";
    this->depth = 0;

    traverseAST(this, ast);

    spdlog::info("Symbol Table population done");
}

/**
 * @brief Create symbol table with specified ID (don't use this to create from AST root node!)
 * 
 * @param ast The AST to build from
 * @param tableID The ID to assign to this table
 */
SymbolTable::SymbolTable(SymbolTable* parent, AST* ast, uint tableID, std::string name)
{
    this->tableID = tableID;
    this->name = name;
    this->parent = parent;
    this->depth = parent->depth + 1;

    traverseAST(this, ast);
}

/**
 * @brief Internal recursive print function
 * 
 * @param st Symbol table to print
 * @param depth Depth of this iteration
 */
void stprint(SymbolTable* st, uint depth)
{
    // Do not print empty tables
    // if (st->table.size() == 0) return;

    // Construct the padding string using bit flags
    std::string padding;
    for (int i = 0; i < st->depth; ++i) {
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

/**
 * @brief Print this symbol table
 */
void SymbolTable::print()
{
    stprint(this, 0);
}