#pragma once

#include <codeGeneration/CodeGenerator.hpp>

struct ArgHash
{
    std::size_t operator()(const Arg& arg) const {
        return std::hash<std::string>{}(arg.toString());
    }
};

class MemoryAllocator
{
public:
    CodeGenerator& codeGen;

    int stackSize; // Used to determine offset

	std::vector<bool> regOccupied;               // Indexed by register enum
	std::unordered_map<Arg, Register, ArgHash> regMap;   // Maps name to occupied register
	std::unordered_map<Arg, int, ArgHash> stackOffsetMap;   // Maps name to offset in stack

    MemoryAllocator(CodeGenerator& codeGen);

    InstrArg getReg(const Arg& arg);
    void save(const Arg& arg);
    void deregister(const Arg& arg);

private:
    Register getNextAvailReg(const Arg& arg);
};