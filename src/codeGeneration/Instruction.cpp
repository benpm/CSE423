#include <codeGeneration/Instruction.hpp>
#include <magic_enum.hpp>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/formatter.h>

std::string InstrArg::toString() const
{   
    if (std::holds_alternative<Register>(this->arg)) {
        Register reg = std::get<Register>(this->arg);
        return fmt::format("%{}", magic_enum::enum_name(reg));
    } else if (std::holds_alternative<std::pair<Register, int>>(this->arg)) {
        std::pair<Register, int> memLoc = std::get<std::pair<Register, int>>(this->arg);
        return fmt::format("{}(%{})", 
            memLoc.second,
            magic_enum::enum_name(memLoc.first)
        );
    } else if (std::holds_alternative<std::pair<Register, std::string>>(this->arg)) {
        std::pair<Register, std::string> memLoc = std::get<std::pair<Register, std::string>>(this->arg);
        return fmt::format("{}(%{})", 
            memLoc.second,
            magic_enum::enum_name(memLoc.first)
        );
    } else if (std::holds_alternative<int>(this->arg)) {
        int imm = std::get<int>(this->arg);
        return fmt::format("${}", imm);
    } else if (std::holds_alternative<float>(this->arg)) {
        float imm = std::get<float>(this->arg);
        return fmt::format("${:f}", imm);
    } else if (std::holds_alternative<char>(this->arg)) {
        char imm = std::get<char>(this->arg);
        return fmt::format("${}", imm);
    } else if (std::holds_alternative<std::string>(this->arg)) {
        return std::get<std::string>(this->arg);
    }

    spdlog::error("Instruction arg cannot be converted to string!");
    return "Frick";
}

std::map<Instruction::OpCode, std::string> opToStr {
    {Instruction::OpCode::ADD,  "add"},
    {Instruction::OpCode::IMUL, "imul"},
    {Instruction::OpCode::IDIV, "idiv"},
    {Instruction::OpCode::SUB,  "sub"},
    {Instruction::OpCode::NEG,  "neg"},
    {Instruction::OpCode::MOV,  "mov"},
    {Instruction::OpCode::PUSH, "push"},
    {Instruction::OpCode::POP,  "pop"},
    {Instruction::OpCode::JMP,  "jmp"},
    {Instruction::OpCode::JE,   "je"},
    {Instruction::OpCode::JNE,  "jne"},
    {Instruction::OpCode::JG,   "jg"},
    {Instruction::OpCode::JGE,  "jge"},
    {Instruction::OpCode::JL,   "jl"},
    {Instruction::OpCode::JLE,  "jle"},
    {Instruction::OpCode::JZ,   "jz"},
    {Instruction::OpCode::JNZ,  "jnz"},
    {Instruction::OpCode::RET,  "ret"},
    {Instruction::OpCode::CALL, "call"},
    {Instruction::OpCode::CMP,  "cmp"}
};

std::string Instruction::toString() const
{
    if (this->asmDirective.size() != 0) {
        return this->asmDirective;
    }

    std::string str = fmt::format("\t{} ", opToStr.at(this->opCode));
    for (int i = 0; i < this->args.size(); i++) {
        std::string fmtstr = (i < this->args.size() - 1) ? "{}, "  : "{}";
        str += fmt::format(fmtstr, args.at(i).toString());
    }

    if (this->comment.size() != 0) {
        str += fmt::format(" # {}", this->comment);
    }

    return str;
}