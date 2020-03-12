#pragma once

#include <string>
#include <vector>

union ArgVal
{
    uint label;
    int ival;
    char cval;
    float fval;
    char* sval;
};

class Statement
{
public:
    enum Type {
        // Binary operator [result] [operand A] [operand B]
        ADD, MUL, DIV, SUB, MOD,
        // Unary operator [result] [operand]
        MINUS, NOT,
        // Unconditional jump to basic block label [BB label]
        JUMP,
        // Conditional comparison jump to basic block label [BB label] [A] [B]
        JUMP_IF_LT, JUMP_IF_GT, JUMP_IF_LE, JUMP_IF_GE, JUMP_IF_EQ, JUMP_IF_NEQ,
        // Conditional true/false jump to basic block label [BB label] [check]
        JUMP_IF_TRUE,
        // Return statement [return value]
        RETURN,
        // Break statement
        BREAK,
        // Function call with arguments [function] [args...]
        CALL,
        // Do nothing
        NO_OP
    };

    Type type = Type::NO_OP;
    std::vector<ArgVal> args;

    Statement(Type type);
    Statement(Type type, ArgVal a);
    Statement(Type type, ArgVal a, ArgVal b);
    Statement(Type type, ArgVal a, ArgVal b, ArgVal c);
};