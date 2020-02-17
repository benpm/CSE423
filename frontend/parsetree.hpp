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

typedef struct Tree {
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

    // Map enum to string for nonterminals
    static std::vector<std::string> nonTerminalStr;
    // Map enum to string for terminal
    static std::vector<std::string> terminalStr;


    Terminal value; // Stores terminal if this node is a terminal
    NonTerminal identifier;  // Stores nonterminal if this node is a nonterminal
    std::vector<struct Tree*> nodes; // Reference children

    Tree(Terminal value, NonTerminal identifier, std::vector<struct Tree*> nodes) :
        value(value), identifier(identifier), nodes(nodes) {};

    void print(); // Print the parse tree

} *ParseTree;
