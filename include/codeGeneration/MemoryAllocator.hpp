#pragma once

#include <codeGeneration/CodeGenerator.hpp>
#include <codeGeneration/Instruction.hpp>
#include <unordered_set>

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

    int stackSize = 0; // Used to determine offset

	std::vector<bool> regOccupied;               // Indexed by register enum
	std::unordered_map<Arg, InstrArg, ArgHash> regMap;   // Maps name to occupied register
	std::unordered_map<Arg, InstrArg, ArgHash> storageMap;   // Maps name to offset in stack

    MemoryAllocator(CodeGenerator& codeGen);

    InstrArg getLoc(const Arg& arg);
    InstrArg allocateReg(const Arg& arg);
    void save(const Arg& arg);
    void deregister(const Arg& arg);
    void deregister(const std::unordered_set<Arg, ArgHash> args);
    void evict(Register reg);
    void clear();
    void insertAt(const Arg& arg, Register reg);
    void parameter(const Arg& arg, int n);
    void allocateArg(const Arg& arg);
private:
    Register getNextAvailReg(const Arg& arg);
};