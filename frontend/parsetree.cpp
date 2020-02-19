/**
 * @file parsetree.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of tree structure to represent a parse tree
 * @date 2020-02-11
 * 
 */
#include <iostream>
#include <string>
#include <parsetree.hpp>

// Map enum to string for terminals
std::vector<std::string> Node::terminalStr {
    "INT", "FLOAT", "CHAR", "FOR", "WHILE", "IF", "ELSE", "RETURN", "BREAK", "SEMICOLON",
    "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "EQUAL", "PLUS",
    "MINUS", "TIMES", "DIVIDE", "MODULO", "PLUSEQUAL", "MINUSEQUAL", "TIMESEQUAL",
    "DIVEQUAL", "MODEQUAL", "INCR", "DECR", "LT", "GT", "LE", "GE", "ISEQ", "NOTEQ", "LOGAND",
    "LOGOR", "NOT", "STRINGLIT", "CHARLIT", "INTCONST", "FLOATCONST", "ID", "ARRAY_ID",
    "EPSILON", "NONE"
};

// Map enum to string for nonterminals
std::vector<std::string> Node::nonTerminalStr {
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
 * @brief Convert an enumerated Terminal symbol to a string
 */
const std::string Node::toTerminal(Node::Terminal t)
{
    return this->terminalStr.at(t);
}

/**
 * @brief Convert an enumerated NonTerminal symbol to a string
 */
const std::string Node::toNonTerminal(Node::NonTerminal nt)
{
    return this->nonTerminalStr.at(nt);
}

/**
 * @brief Pretty print the parse tree to standard output
 * 
 */
void Node::print()
{
    this->printNode(*this, 0);
}

/**
 * @brief Pretty print a node and recursively print its children
 * @details Uses a simple prefix DFS tree traversal algorithm
 */
void Node::printNode(Node &node, int depth)
{
    std::string printStr;
    const std::string padding(depth * 3, ' ');

    // Print the terminal string if applicable,
    // otherwise print the nonterminal string
    if (node.value != Node::Terminal::NONE)
        printStr = node.toTerminal(node.value);
    else
        printStr = node.toNonTerminal(node.identifier);

    // Print a graphical depiction of the branch
    std::cout << padding << "`-" << printStr << std::endl;

    // Recur on the node's children
    for (auto it : node.children)
        printNode(*it, depth + 1);
}
