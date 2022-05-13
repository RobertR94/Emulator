#pragma once
#include <string>

#include "Memory.h"
#include "Register.h"
#include "ControlUnit.h"
#include "CpuState.h"

class Cpu
{
    private:
        ControlUnit controlUnit;
        CpuState cpuState;

    public:

        Registers registers;
        Memory* memory;

    private:
        void resetCpuState();

    public:
        Cpu(Memory* mem);
        CpuState runProgram(std::string& name);
           
};
