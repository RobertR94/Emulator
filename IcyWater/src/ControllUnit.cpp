#include <iostream>

#include "memory.h"
#include "ControllUnit.h"

#define DivZeroInf(a, b) std::cout << "Div: " << a << ", " << b << std::endl;


int ControllUnit::UpdateInstructionRegister()
{   
    /* Coderitter: Auch witzig, das man hier über einen Parameter einfach die Größe der
    Instuktionen verändern könnte. Würde dann aber nicht mehr ganz zur Computing-Unit passen.
    Daher hätte man das sogar fest einprogrammieren können, sogar ohne Schleife. Hier kommt 
    das Prinzip zum Einsatz, dass man in den Code nur die Features einbaut, die man wirklich
    braucht, denn jedes Feature kostet und man will kein Geld ausgeben für Dinge, die im Moment
    noch keinen Nutzen bringen. Sehr wichtiges Prinzip. Du hättest es z.B. auch so hier schreiben 
    können, dann wird es einfacher.
    
    instruction_register[0] = memory[instruction_cnt_register];
    instruction_register[1] = memory[instruction_cnt_register + 1];
    instruction_register[2] = memory[instruction_cnt_register + 2];
    instruction_register[3] = memory[instruction_cnt_register + 3];

    Eine weitere Kritik ist vielleicht, dass der Methodenname hätte passender sein können, z.B.
    'ReadNextInstructionFromMemory'.
    */
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

/* Coderitter: Nach dem Inhalt her werden hier die Rechenoperationen ausgeführt. Eventuell könnte die Methode
dann auch anders heißen, sowas wie ExecuteInstruction. */
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