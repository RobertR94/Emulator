#include <iostream>


#include "Cpu.h"
#include "Interpreter.h"


#define print(x) std::cout << x << std::endl;
unsigned char memory[256];


/* Coderitter: Es sieht besser aus, wenn nicht so viele Leerzeilen verwendet werden. 
Am Besten nur eins, das reicht aus und hält die Anzahl der Leerzeilen konstant. */


int main()
{
    /* Coderitter: Schön, dass du an so ein Detail gedacht hast, wie den Speicher
    mit Nullen zu füllen. */
    //Memory: Address 0-127 is the text segment(holding the programm)
    //Address 128-255 memory for load and store operations
    //Init to 0 at every Adrress
    std::fill(memory, memory+256, 0b00000000);

    Cpu icy_water;
    icy_water.Run();

    
    return 0;
}