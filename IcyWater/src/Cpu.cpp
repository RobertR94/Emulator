#include <vector>

#include "Cpu.h"


Cpu::Cpu(Memory* mem)
{
    memory = mem;
    return;
}

void Cpu::resetCpuState()
{
    cpuState = CpuState::OK;
    return;
}

CpuState Cpu::runProgram(std::string& name)
{   
    registers.resetInstructionCntRegister();
    registers.resetIstructionRegister();
    registers.resetCRegister();

    resetCpuState();
    
    memory->loadBinaryIntoMemory(registers.binaryPathRegister, registers.binaryPosRegister);
  
    while(cpuState == CpuState::OK)
    {   
        if(registers.instructionCntRegister > memory->bound)
        {
            registers.resetInstructionCntRegister();
            memory->loadBinaryIntoMemory(registers.binaryPathRegister, registers.binaryPosRegister);
        }
        registers.readInstructionFromMemory(memory);
        controlUnit.executeInstruction(&registers, memory, &cpuState);     
    }
    registers.resetBinaryPosRegister();
    registers.resetBinaryPathRegister();
    
    return cpuState;
   
}



