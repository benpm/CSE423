#include <codeGeneration/CodeGenerator.hpp>
#include <codeGeneration/MemoryAllocator.hpp>
#include <map>

CodeGenerator::CodeGenerator(const Program& program)
{
    // <-- Insert program header stuff HERE
    for (const auto& pair : program.functions) {
        this->genFunction(pair.second);
    }
}

void CodeGenerator::genFunction(const Function& func)
{
    MemoryAllocator allocator(*this);

    // <-- Insert function header stuff HERE
    for (const BasicBlock& block : func.blocks) {
        // <-- Insert label
        for (const Statement& stmt : block.statements) {
            this->genStatement(allocator, stmt);
        }
    }
}

void CodeGenerator::genStatement(MemoryAllocator& allocator, const Statement& stmt)
{
    switch(stmt.type) {
        case Statement::ADD: this->genADD(allocator, stmt); break;
        default: /* throw "Unhandled statement type"; */ break;
    }
}

void CodeGenerator::genADD(MemoryAllocator& allocator, const Statement& stmt)
{
    
}

void CodeGenerator::printInstructs()
{
    for (const Instruction& instr : this->instrs)
    {
        fmt::print("{}\n", instr.toString());
    }
}

std::string InstrArg::toString() const
{
    if (std::holds_alternative<Register>(this->arg)) {
        return fmt::format("%")
    }
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

    std::string str = fmt::format("{} ", opToStr.at(this->opCode));
    for (const InstrArg& arg : this->args) 
        str += fmt::format(", {}", arg.toString());
    str += "\n";

    return str;
}