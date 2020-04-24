#pragma once

#include <CodeGenerator.hpp>

class MemoryAllocator
{
public:
    enum Register {
		EAX, EBX, ECX, FAX // Not a real register, but this holds floats too
	};
	
    CodeGenerator& codeGen;

    int stackSize; // Used to determine offset

	std::vector<bool> regOccupied;               // Indexed by register enum
	std::map<std::string, Register> intRegMap;   // Maps name to occupied register
	std::map<std::string, Register> floatRegMap; // Maps name to occupied register
	std::map<std::string, int> stackOffsetMap;   // Maps name to offset in stack

    MemoryAllocator(CodeGenerator& codeGen);

    std::string getReg(const Arg& arg);
    std::string getNextAvailReg(const Arg& arg);
    void save(std::string reg, const Arg& arg);
    void deregister(const Arg& arg);
};
