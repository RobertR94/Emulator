#include <iostream>
#include <string>

#include "Cpu.h"
#include "Compiler.h"
#include "Memory.h"
#include "Os.h"
#include "ControlUnit.h"

int main()
{
    //Memory, cpu  and the os are representing the System (System could be a class) 
    //Memory: Address 0-127 is the text segment(holding the programm)
    //Address 128-255 memory for load and store operations
    //Init to 0 at every Adrress
    Memory memory;
    Os operatingSystem;
    Cpu cpu(&memory);

    operatingSystem.run(&cpu);
  
    return 0;
}