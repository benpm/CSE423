/**
 * @file parsetree.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header Tree structure to represent a parse tree
 * @date 2020-02-11
 * 
 */
#pragma once

#include <string>
#include <vector>

typedef class Node {
public:
    // Enum storing terminals
    enum Terminal {
        INT, FLOAT, CHAR, FOR, WHILE, IF, ELSE, RETURN, BREAK, SEMICOLON,
        COMMA, LPAREN, RPAREN, LBRACE, RBRACE, LBRACK, RBRACK, EQUAL, PLUS,
        MINUS, TIMES, DIVIDE, MODULO, PLUSEQUAL, MINUSEQUAL, TIMESEQUAL,
        DIVEQUAL, MODEQUAL, INCR, DECR, LT, GT, LE, GE, ISEQ, NOTEQ, LOGAND,
        LOGOR, NOT, STRINGLIT, CHARLIT, INTCONST, FLOATCONST, ID, ARRAY_ID,
        EPSILON, NONE
    };

    // Enum storing non terminals
    enum NonTerminal {
        PROGRAM, DECLARATION_LIST, DECLARATION, VAR_DECLARATION,
        SCOPED_VAR_DECLARATION, VAR_DECL_LIST, VAR_DECL_INITIALIZE,
        VAR_DECL_ID, SCOPED_TYPE_SPECIFIER, TYPE_SPECIFIER,
        FUN_DECLARATION, PARAMS, PARAM_LIST, PARAM_ID, STATEMENT,
        EXPRESSION_STMT, EXPRESSION, MUTABLE, ASSIGN_OP, UNARY_ASSIGN_OP,
        SIMPLE_EXPRESSION, AND_EXPRESSION, UNARY_REL_EXPRESSION,
        REL_EXPRESSION, REL_OP, SUM_EXPRESSION, SUM_OP, MUL_EXPRESSION,
        MUL_OP, UNARY_EXPRESSION, UNARY_OP, FACTOR, IMMUTABLE, CALL,
        ARGS, ARG_LIST, CONSTANT, COMPOUND_STMT, LOCAL_DECLARATIONS,
        STATEMENT_LIST, SELECTION_STMT, ELSE_IF_LIST, ITERATION_STMT,
        WHILE_STMT, FOR_STMT, RETURN_STMT, BREAK_STMT
    };

    Terminal value;              // Stores terminal if this node is a terminal
    NonTerminal identifier;      // Stores nonterminal if this node is a nonterminal
    std::vector<Node*> children; // Reference children
    int lineNum = -1;            // Stores line number grammar rule was found on

    Node(Terminal value, NonTerminal identifier, std::vector<Node*> children, int lineNum) :
        value(value), identifier(identifier), children(children), lineNum(lineNum) {};

    const std::string toTerminal(Terminal t); // Convert terminal enum to string
    const std::string toNonTerminal(NonTerminal nt); // Convert nonterminal enum to string
    void print(); // Print the parse tree

private:
    // Map enum to string for nonterminals
    static std::vector<std::string> nonTerminalStr;
    // Map enum to string for terminal
    static std::vector<std::string> terminalStr;

    void printNode(Node &node, int depth);

} *ParseTree;
