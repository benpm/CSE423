#pragma once

#include <string>
#include <vector>

struct Arg
{
    // Stored value of argument
    union Val {
        uint label;
        int ival;
        char cval;
        float fval;
        char* sval;
    };
    Val val;

    // Type of argument
    enum Type {
        LABEL, INT, CHAR, FLOAT, NAME
    };
    Type type;

    Arg(uint label) { type = Type::LABEL; val.label = label; };
    Arg(int ival)   { type = Type::INT; val.ival = ival; };
    Arg(char cval)  { type = Type::CHAR; val.cval = cval; };
    Arg(float fval) { type = Type::FLOAT; val.fval = fval; };
    Arg(char* sval) { type = Type::NAME; val.sval = sval; };

    std::string toString() const;
};

class Statement
{
public:
    enum Type {
        // Binary operator [result] [operand A] [operand B]
        ADD, MUL, DIV, SUB, MOD,
        // Unary operator [result] [operand]
        MINUS, NOT, ASSIGN,
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
    std::vector<Arg> args;

    Statement(Type type);
    Statement(Type type, Arg a);
    Statement(Type type, Arg a, Arg b);
    Statement(Type type, Arg a, Arg b, Arg c);
    Statement(Type type, std::vector<Arg>& args);
    std::string toString() const;
};