/**
 * @file parsetree.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of tree structure to represent a parse tree
 * @date 2020-02-11
 * 
 */
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <parsetree.hpp>

// Map enum to string for terminals
std::vector<std::string> Tree::terminalStr {
    "INT", "FLOAT", "CHAR", "FOR", "WHILE", "IF", "ELSE", "RETURN", "BREAK", "SEMICOLON",
    "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "EQUAL", "PLUS",
    "MINUS", "TIMES", "DIVIDE", "MODULO", "PLUSEQUAL", "MINUSEQUAL", "TIMESEQUAL",
    "DIVEQUAL", "MODEQUAL", "INCR", "DECR", "LT", "GT", "LE", "GE", "ISEQ", "NOTEQ", "LOGAND",
    "LOGOR", "NOT", "STRINGLIT", "CHARLIT", "INTCONST", "FLOATCONST", "ID", "ARRAY_ID",
    "EPSILON", "NONE"
};

// Map enum to string for nonterminals
std::vector<std::string> Tree::nonTerminalStr {
    "PROGRAM", "DECLARATION_LIST", "DECLARATION", "VAR_DECLARATION",
    "SCOPED_VAR_DECLARATION", "VAR_DECL_LIST", "VAR_DECL_INITIALIZE",
    "VAR_DECL_ID", "SCOPED_TYPE_SPECIFIER", "TYPE_SPECIFIER",
    "FUN_DECLARATION", "PARAMS", "PARAM_LIST", "PARAM_ID", "STATEMENT",
    "EXPRESSION_STMT", "EXPRESSION", "MUTABLE", "ASSIGN_OP", "UNARY_ASSIGN_OP",
    "SIMPLE_EXPRESSION", "AND_EXPRESSION", "UNARY_REL_EXPRESSION",
    "REL_EXPRESSION", "REL_OP", "SUM_EXPRESSION", "SUM_OP", "MUL_EXPRESSION",
    "MUL_OP", "UNARY_EXPRESSION", "UNARY_OP", "FACTOR", "IMMUTABLE", "CALL",
    "ARGS", "ARG_LIST", "CONSTANT", "COMPOUND_STMT", "LOCAL_DECLARATIONS",
    "STATEMENT_LIST", "SELECTION_STMT", "ELSE_IF_LIST", "ITERATION_STMT",
    "WHILE_STMT", "FOR_STMT", "RETURN_STMT", "BREAK_STMT"
};

/**
 * @brief 
 * 
 */
void Tree::print()
{
    // Keep track of current node
    ParseTree cur = this;

    int row_cnt = 0;
    int cnt = 1;

    // Create a queue for BFS 
    std::queue<ParseTree> q; 
  
    // Enqueue the current node
    q.push(cur); 
  
    while(!q.empty()) { 
        // Dequeue a vertex from queue and print it 
        cur = q.front();
        q.pop(); 

        cnt--;
        
        if (cur->value != Tree::Terminal::NONE) {
            if (cnt > 0)
                std::cout << Tree::terminalStr[cur->value] << "   ";
            else
                std::cout << Tree::terminalStr[cur->value] << "\n";
        } else {
            if (cnt > 0)
                std::cout << Tree::nonTerminalStr[cur->identifier] << "   ";
            else
                std::cout << Tree::nonTerminalStr[cur->identifier] << "\n";
        }
  
        // Get all child nodes of the current node
        row_cnt += cur->nodes.size();
        for (auto i = cur->nodes.begin(); i != cur->nodes.end(); i++)
            q.push(*i); 

        if (cnt == 0) {
            cnt = row_cnt;
            row_cnt = 0;
        }
    } 
}
