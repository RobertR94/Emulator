#include <iostream>
#include "Register.h"

Registers::Registers()
{
    resetBinaryPathRegister();
    resetBinaryPosRegister();
    resetCRegister();
    resetInstructionCntRegister();
    resetIstructionRegister();
}


void Registers::readInstructionFromMemory(Memory *memory)
{   

    instructionRegister[0] = memory->mem[instructionCntRegister + 0];
    instructionRegister[1] = memory->mem[instructionCntRegister + 1];
    instructionRegister[2] = memory->mem[instructionCntRegister + 2];
    instructionRegister[3] = memory->mem[instructionCntRegister + 3];

    instructionCntRegister += 4;
    return;
}

void Registers::resetBinaryPathRegister()
{
    binaryPathRegister = "";
    return;
}

void Registers::resetBinaryPosRegister()
{
    binaryPosRegister = 0b00000000;
    return;
}

void Registers::resetCRegister()
{
    std::fill(cRegister, cRegister+8, 0b00000000);
    return;
}

void Registers::resetInstructionCntRegister()
{
    instructionCntRegister = 0b00000000;
    return;
};

void Registers::resetIstructionRegister()
{
    std::fill(instructionRegister, instructionRegister+4, 0b00000000);
    return;
}
