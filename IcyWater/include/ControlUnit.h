#pragma once
#include <string>

#include "ArithmeticLogicUnit.h"
#include "Register.h"
#include "CpuState.h"


class ControlUnit
{

    private:
        ArithmeticLogicUnit arithmeticLogicUnit;
        int state;
                       
    public:

    private:
        
    public:       
        //Interprete Instructions
        void executeInstruction(Registers* registers, Memory* memory, CpuState* cpuState);
        
};
