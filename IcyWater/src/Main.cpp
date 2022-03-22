#include <iostream>
#include <string>
#include <sstream>
#include <bitset>


#include "Cpu.h"
#include "Interpreter.h"


#define print(x) std::cout << x << std::endl;
unsigned char memory[256];





int main()
{

    //Memory: Address 0-127 is the text segment(holding the programm)
    //Address 128-255 memory for load and store operations
    //Init to 0 at every Adrress
    std::fill(memory, memory+256, 0b00000000);

    Cpu icy_water;
    icy_water.Run();
    Interpreter i;
//    i.Test("/home/robert/MyProgramms/Challenge/Emulator/IcyWater/binaries/challenge.S.hex");

    
    return 0;
}