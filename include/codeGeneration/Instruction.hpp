#pragma once

#include <variant>
#include <string>
#include <vector>
#include <spdlog/formatter.h>
#include <ir/statement.hpp>

// When adding registers, make sure to update USABLE_REGS
// The size of regOccupied should be the number of registers we can USE (i.e. we cannut "USE" ebp/esp/pc)
#define USABLE_REGS 4
enum Register {
    // Usable registers
    eax, ebx, ecx, edx,
    // Unusable registers
    no_reg,
    esp = 126,
    ebp = 127
};

class InstrArg
{
public:
    std::variant<
        int,           // Integer immediate    
        float,         // Float immediate
        char,          // Character immediate
        std::string,   // Label/function name
        Register,      // Register
        std::pair<Register, int> // Mem address with offset i.e. -12(%ebp)
    > arg;

    std::string toString() const;

    InstrArg(const Arg& arg)           {
        switch (arg.type) {
        case Arg::FLOAT: this->arg = arg.val.fval; break;
        case Arg::INT:   this->arg = arg.val.ival; break;
        case Arg::CHAR:  this->arg = arg.val.cval; break;
        case Arg::LABEL: this->arg = fmt::format("BB{}", arg.val.label); break;
        default:
            spdlog::error("Cannot handle given immediate arg type"); exit(EXIT_FAILURE);
            break;
        }
    };
    InstrArg(int   imm)                {this->arg = imm;};
    InstrArg(float imm)                {this->arg = imm;};
    InstrArg(char  imm)                {this->arg = imm;};
    InstrArg(std::string label)        {this->arg = label;};
    InstrArg(Register reg)             {this->arg = reg;};
    InstrArg(Register reg, int offset) {this->arg = std::pair<Register, int>{reg, offset};};
};

class Instruction
{
private:
public:
    enum OpCode {
        ADD,   // add  src, dest | adds src to dest and stores in dest
        IMUL,  // imul src, dest | multiplies src by dest and stores in dest
        IDIV,  // IDIV divisor   | Divides EAX by divisor, quotient in EAX, remainder in EDX
        SUB,   // sub src, dest  | subtracts src from dest into dest
        NEG,   // neg arg        | arithmetic negation 
        MOV,   // mov src, dest  | moves data from src to dest
        PUSH,  // push arg       | pushes data onto stack
        POP,   // pop dest       | pop data from stack into dest
        JMP,   // jmp loc        | Unconditionally jump to location     
        JE,    // je loc         | Jump if equal, checks if ZF = 1
        JNE,   // jne loc        | Jump if not equal, checks if ZFs = 0
        JG,    // jge loc        | Jump if > , check if SF == OF and ZF == 0
        JGE,   // jge loc        | Jump if >=, check if SF == OF _OR_ ZF == 0
        JL,    // jl loc         | Jump if <, check if SF != OF
        JLE,   // jle loc        | Jump if <=, check if SF != OF _OR_ ZF == 1
        JZ,    // jz  loc        | Jump if == 0, check if ZF == 1
        JNZ,   // jnz loc        | Jump if != 0, check if ZF == 0
        RET,   // ret [val]      | Loads next val on the stack into EIP, and then pops the specified number of bytes off the stack. If val not supplied, instruction will not pop any vals
        CALL,  // call loc       | Pushes the addr of the instr AFTER call instr to top of the stack, jumps to loc
        CMP    // cmp arg0, arg1 | arg1 - arg0, sets flags
    };

    OpCode opCode;
    std::string asmDirective; // Holds arbitrary string needed in creating assembly (i.e. )
    std::string comment;

    std::vector<InstrArg> args;

    Instruction(OpCode opCode, const std::vector<InstrArg> args)
        : opCode(opCode), args(args) {};
    Instruction(OpCode opCode, const std::vector<InstrArg> args, std::string comment) 
        : opCode(opCode), args(args), comment(comment) {};
    Instruction(std::string asmDirective) : asmDirective(asmDirective) {};

    std::string toString() const;
};