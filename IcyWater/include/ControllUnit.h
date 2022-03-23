#pragma once
#include <string>
#include <ComputingUnit.h>



class ControllUnit
{

    private:
        ComputingUnit cpu;
        
        //memory address for the next instruction 
        unsigned char instruction_cnt_register;
        //holds instruction Operator operand1 operand2 operand3
        //E.g Add a1 a2 a3
        unsigned char instruction_register[4];
        const short instruction_size = 4;

        //1 zero register[7]
        //7 gp register[0-6]
        unsigned char cregister[8];
       
    public:
        enum State
        {
            OK,
            DvisionByZero,
            MemoryFault,
            Invalid,
            OutOfMemory,
            Exit
        };


    private:
        void PrintOP(std::string op, unsigned char a, unsigned char b);
        bool IsZero(unsigned char n);
    
    public:
        ControllUnit()
        {
            instruction_cnt_register = 0b00000000;
            std::fill(instruction_register, instruction_register+4, 0b00000000);
            std::fill(cregister, cregister+8, 0b00000000);
            
        }
        //Load instrcution from memory into the instruction_register
        int UpdateInstructionRegister();
        //Interprete Instructions
        int ReadInstruction();
        //Reset all general purpose registers to zero
        void ResetGPRegister();
        //Rest instruction count and instruction register to zero
        void RestControllRegister();

        

};
