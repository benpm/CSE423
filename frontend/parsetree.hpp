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

union PTNodeData
{
    int ival;
    float fval;
    char *sval;
    char cval;
};


class PTNode {
public:
    // Label
    enum Label {
        INT, FLOAT, CHAR, FOR, WHILE, IF, ELSE, RETURN, BREAK, SEMICOLON,
        COMMA, LPAREN, RPAREN, LBRACE, RBRACE, LBRACK, RBRACK, EQUAL, PLUS,
        MINUS, TIMES, DIVIDE, MODULO, PLUSEQUAL, MINUSEQUAL, TIMESEQUAL,
        DIVEQUAL, MODEQUAL, INCR, DECR, LT, GT, LE, GE, ISEQ, NOTEQ, LOGAND,
        LOGOR, NOT, STRINGLIT, CHARLIT, INTCONST, FLOATCONST, ID, ARRAY_ID,
        EPSILON, NONE,

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
        WHILE_STMT, FOR_STMT, RETURN_STMT, BREAK_STMT, FUN_NAME
    };

    bool terminal = true;
    Label label = Label::NONE;
    std::vector<PTNode*> children; // Reference children
    int lineNum = -1;            // Stores line number grammar rule was found on
    PTNodeData data;


    PTNode() {};
    PTNode(Label label, std::vector<PTNode*> children, int lineNum);
    PTNode(Label label, int lineNum);

    const std::string toString() const;
    void print(); // Print the parse tree

private:
    // Map enum to string for terminal
    static std::vector<std::string> str;

    void printNode(PTNode &node, int depth);

};
