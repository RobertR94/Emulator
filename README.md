# Emulator

Small cpu emulator

You can add and edit assembler files in the Programs folder. The emulator translates the assembly files into binary files and then executes the binary instructions.

Instruction set:

add r1 r2 r3
sub r1 r2 r3 
mul r1 r2 r3
div r1 r2 r3
addi r1 r2 number
subi r1 r2 number
muli r1 r2 number
divi r1 r2 number
LD r1 adr address   #Load content stored at address into r1
ST r1 adr address   #Store content of r1 into memory at addres


We haven a 256 byte memory, of which bytes 0-127 are reserved for the executable and bytes 128 - 255 for load and store operations.
There are 8 registers: 7 genearal purpose register a1-a7 and one zero register x0.