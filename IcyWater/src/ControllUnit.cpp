#include <iostream>

#include "memory.h"
#include "ControllUnit.h"

#define DivZeroInf(a, b) std::cout << "Div: " << a << ", " << b << std::endl;


int ControllUnit::UpdateInstructionRegister()
{   

    for(int i = 0; i < instruction_size; i++)
    {   
        if(instruction_cnt_register > bound)
        {
            return OutOfMemory;
        }
        instruction_register[i] = memory[instruction_cnt_register];
        instruction_cnt_register++;
    }


    return OK;
}


void ControllUnit::PrintOP(std::string op, unsigned char a, unsigned char b)
{
    std::cout << op << ": " << +a << " and " << +b << std::endl;
}


int ControllUnit::ReadInstruction()
{       

    switch (instruction_register[0])
    {
    case 0x00:
        
        cregister[instruction_register[1]] = cpu.Add(cregister[instruction_register[2]], cregister[instruction_register[3]]);
        return OK;
    
    case 0x01:
        
        cregister[instruction_register[1]] = cpu.Sub(cregister[instruction_register[2]], cregister[instruction_register[3]]);
        return OK;
    
    case 0x02:
    
        cregister[instruction_register[1]] = cpu.Mul(cregister[instruction_register[2]], cregister[instruction_register[3]]);
        return OK;

    case 0x03:
        if(cregister[instruction_register[3]] == 0x00)
        {
            DivZeroInf(+(cregister[instruction_register[2]]), +(cregister[instruction_register[3]]))
            return DvisionByZero;
        }
        cregister[instruction_register[1]] = cpu.Div(cregister[instruction_register[2]], cregister[instruction_register[3]]);
        return OK;
    
    case 0x04:
        cregister[instruction_register[1]] = cpu.Add(cregister[instruction_register[2]], instruction_register[3]);
        return OK;
    
    case 0x05:
        cregister[instruction_register[1]] = cpu.Sub(cregister[instruction_register[2]], instruction_register[3]);
        return OK;
    
    case 0x06:
        cregister[instruction_register[1]] = cpu.Mul(cregister[instruction_register[2]], instruction_register[3]);
        return OK;
    
    case 0x07:
        if(instruction_register[3] == 0x00)
        {
            DivZeroInf(+(cregister[instruction_register[2]]), +(instruction_register[3]));
            return DvisionByZero;
        }
        cregister[instruction_register[1]] = cpu.Div(cregister[instruction_register[2]], instruction_register[3]);
        return OK;
    
    case 0x08:
        if(instruction_register[3] <= 0x7f && instruction_register[3] > 0xFF)
        {
            return MemoryFault;
        }
        memory[instruction_register[3]] = cregister[instruction_register[1]];
        return OK;
    
    case 0x09:
        if(instruction_register[3] <= 0x7f && instruction_register[3] > 0xFF)
        {
            return MemoryFault;
        }
        cregister[instruction_register[1]] = memory[instruction_register[3]];
        return OK;
    
    default:
        if(instruction_register[0] == 0xFF && instruction_register[1] == 0xFF && instruction_register[2] == 0xFF && instruction_register[3] == 0xFF)
        {
            return Exit;
        }
        return Invalid;
    }
    return Invalid;
}

void ControllUnit::ResetGPRegister()
{
    
    std::fill(cregister, cregister+8, 0b00000000);
}


void ControllUnit::RestControllRegister()
{
     instruction_cnt_register = 0b00000000;
     std::fill(instruction_register, instruction_register+4, 0b00000000);
}