#include <iostream>

#include "Memory.h"
#include "ControlUnit.h"

#define divZeroInf(a, b) std::cout << "Div: " << a << ", " << b << std::endl;


void ControlUnit::executeInstruction(Registers* registers, Memory* memory, CpuState* cpuState)
{       

    switch (registers->instructionRegister[0])
    {
    case 0x00:        
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.add(registers->cRegister[registers->instructionRegister[2]], registers->cRegister[registers->instructionRegister[3]]);
        *cpuState = CpuState::OK;
        return;
    
    case 0x01:        
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.sub(registers->cRegister[registers->instructionRegister[2]], registers->cRegister[registers->instructionRegister[3]]);
        *cpuState = CpuState::OK;
        return;
    
    case 0x02:    
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.mul(registers->cRegister[registers->instructionRegister[2]], registers->cRegister[registers->instructionRegister[3]]);
        *cpuState = CpuState::OK;
        return;

    case 0x03:
        if(registers->cRegister[registers->instructionRegister[3]] == 0x00)
        {
            divZeroInf(+(registers->cRegister[registers->instructionRegister[2]]), +(registers->cRegister[registers->instructionRegister[3]]))
            *cpuState = CpuState::DvisionByZero;
            return;
        }
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.div(registers->cRegister[registers->instructionRegister[2]], registers->cRegister[registers->instructionRegister[3]]);
        *cpuState = CpuState::OK;
        return;
    
    case 0x04:
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.add(registers->cRegister[registers->instructionRegister[2]], registers->instructionRegister[3]);
        *cpuState = CpuState::OK;
        return;
    
    case 0x05:
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.sub(registers->cRegister[registers->instructionRegister[2]], registers->instructionRegister[3]);
        *cpuState = CpuState::OK;
        return;
    
    case 0x06:
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.mul(registers->cRegister[registers->instructionRegister[2]], registers->instructionRegister[3]);
        *cpuState = CpuState::OK;
        return;
    
    case 0x07:
        if(registers->instructionRegister[3] == 0x00)
        {
            divZeroInf(+(registers->cRegister[registers->instructionRegister[2]]), +(registers->instructionRegister[3]));
            *cpuState = CpuState::DvisionByZero;
            return;
        }
        registers->cRegister[registers->instructionRegister[1]] 
        = arithmeticLogicUnit.div(registers->cRegister[registers->instructionRegister[2]], registers->instructionRegister[3]);
        *cpuState = CpuState::OK;
        return;
    
    case 0x08:
        if(registers->instructionRegister[3] <= 0x7f || registers->instructionRegister[3] > 0xFF)
        {
            *cpuState = CpuState::MemoryFault;
            return;
        }
        memory->mem[registers->instructionRegister[3]] = registers->cRegister[registers->instructionRegister[1]];
        *cpuState = CpuState::OK;
        return;
    
    case 0x09:
        if(registers->instructionRegister[3] <= 0x7f || registers->instructionRegister[3] > 0xFF)
        {
            *cpuState = CpuState::MemoryFault;
            return;
        }
        registers->cRegister[registers->instructionRegister[1]] 
        = memory->mem[registers->instructionRegister[3]];
        *cpuState = CpuState::OK;
        return;
    
    default:
        if(registers->instructionRegister[0] == 0xFF && registers->instructionRegister[1] == 0xFF && registers->instructionRegister[2] == 0xFF && registers->instructionRegister[3] == 0xFF)
        {
            *cpuState = CpuState::Exit;
            return;
        }
        
    }
    *cpuState = CpuState::Invalid;
    return;
}



