#include <codeGeneration/Instruction.hpp>
#include <magic_enum.hpp>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/formatter.h>

/**
 * @brief Converts an argument to a string i.e. -10(%rsp)
 * 
 * @return std::string 
 */
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

std::map<OpCode, std::string> opToStr {
    {OpCode::ADD,  "addq"},
    {OpCode::IMUL, "imulq"},
    {OpCode::IDIV, "idivq"},
    {OpCode::SUB,  "subq"},
    {OpCode::NEG,  "negq"},
    {OpCode::MOV,  "movq"},
    {OpCode::PUSH, "pushq"},
    {OpCode::POP,  "popq"},
    {OpCode::JMP,  "jmp"},
    {OpCode::JE,   "je"},
    {OpCode::JNE,  "jne"},
    {OpCode::JG,   "jg"},
    {OpCode::JGE,  "jge"},
    {OpCode::JL,   "jl"},
    {OpCode::JLE,  "jle"},
    {OpCode::JZ,   "jz"},
    {OpCode::JNZ,  "jnz"},
    {OpCode::RET,  "ret"},
    {OpCode::CALL, "call"},
    {OpCode::CMP,  "cmpq"},
    {OpCode::LEA,  "leaq"},
    {OpCode::CQO,  "cqo"}
};

/**
 * @brief Converts and instruction to a string to be output to a file
 * 
 * @return std::string 
 */
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