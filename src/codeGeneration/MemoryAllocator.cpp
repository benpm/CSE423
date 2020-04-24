#include <MemoryAllocator.hpp>

MemoryAllocator::MemoryAllocator(CodeGenerator& codeGen) :
    codeGen(codeGen)
{

}


std::string MemoryAllocator::getReg(const Arg& arg)
{
    return "%rax";
}

std::string MemoryAllocator::getNextAvailReg(const Arg& arg)
{
    return "%rbx";
}

void MemoryAllocator::save(std::string reg, const Arg& arg)
{
    // save reg into name in arg
}

void MemoryAllocator::deregister(const Arg& arg)
{
    // deregister
}
