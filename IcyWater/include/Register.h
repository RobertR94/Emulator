#pragma once
#include <string>

#include "Memory.h"

class Registers
{
    private:

    public:
        std::string binaryPathRegister;
        int binaryPosRegister;

        //memory address for the next instruction 
        unsigned char instructionCntRegister;

        //holds instruction Operator operand1 operand2 operand3
        //E.g Add a1 a2 a3
        unsigned char instructionRegister[4];
        const short instructionSize = 4;

        //1 zero register[7]
        //7 gp register[0-6]
        unsigned char cRegister[8];

    private:

    public:
        Registers();
        void readInstructionFromMemory(Memory *memory);
        void resetInstructionCntRegister();
        void resetIstructionRegister();
        void resetCRegister();
        void resetBinaryPosRegister();
        void resetBinaryPathRegister();


};