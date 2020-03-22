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

// Contains data for tree nodes
union NodeData
{
    int ival;
    float fval;
    char *sval;
    char cval;
};

// Parsetree node class
class PT {
public:
    // Type of node
    enum Label {
        INT, FLOAT, CHAR, FOR, WHILE, IF, ELSE, RETURN, BREAK, GOTO, SEMICOLON,
        COMMA, LPAREN, RPAREN, LBRACE, RBRACE, LBRACK, RBRACK, EQUAL, PLUS,
        MINUS, TIMES, DIVIDE, MODULO, PLUSEQUAL, MINUSEQUAL, TIMESEQUAL,
        DIVEQUAL, MODEQUAL, INCR, DECR, LT, GT, LE, GE, ISEQ, NOTEQ, LOGAND,
        LOGOR, NOT, CHARLIT, INTCONST, FLOATCONST, ID,
        EPSILON, NONE,

        PROGRAM, DECLARATION_LIST, DECLARATION, VAR_DECLARATION,
        SCOPED_VAR_DECLARATION, VAR_DECL_LIST, VAR_DECL_INITIALIZE,
        VAR_DECL_ID, SCOPED_TYPE_SPECIFIER, TYPE_SPECIFIER,
        FUN_DECLARATION, PARAMS, PARAM_LIST, PARAM_ID, STATEMENT,
        EXPRESSION_STMT, EXPRESSION, MUTABLE, ASSIGN_OP, UNARY_ASSIGN_OP,
        SIMPLE_EXPRESSION, AND_EXPRESSION, UNARY_REL_EXPRESSION,
        REL_EXPRESSION, REL_OP, SUM_EXPRESSION, SUM_OP, MUL_EXPRESSION,
        MUL_OP, UNARY_EXPRESSION, FACTOR, IMMUTABLE, CALL,
        ARGS, ARG_LIST, CONSTANT, COMPOUND_STMT, LOCAL_DECLARATIONS,
        STATEMENT_LIST, SELECTION_STMT, ELSE_IF_LIST, ITERATION_STMT,
        WHILE_STMT, FOR_STMT, RETURN_STMT, BREAK_STMT, LABEL_STMT, GOTO_STMT,
        FUN_NAME, UNARY_ASSIGN_EXPRESSION, ELSE_IF, ELSE_STMT, UNARY_MINUS
    };

    // Whether or not this represents a terminal symbol from the grammar
    bool terminal = true;
    // This node's label
    Label label = Label::NONE;
    // Reference children
    std::vector<PT*> children;
    // Stores line number grammar rule was found on
    int lineNum = -1;
    // Data this node contains
    NodeData data;


    PT() {};
    PT(std::string filename);
    PT(Label label, std::vector<PT*> children, int lineNum);
    PT(Label label, int lineNum);

    const std::string toString() const;
    void print();
private:
    // Map label to string
    const static std::vector<std::string> str;

    void printNode(PT &node, int depth, ulong levels);

};
