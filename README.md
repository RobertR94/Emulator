# Emulator

Small cpu emulator

You can add and edit assembler files in the Programs folder. The emulator translates the assembly files into binary files and then executes the binary instructions.

Instruction set:

**add a1 a2 a3**            #Add values in a1 and a2 and store the result in a3<br>
**sub a1 a2 a3**            #Sub values in a1 and a2 and store the result in a3<br>
**mul a1 a2 a3**            #Multiply values in a1 and a2 and store the result in a3<br>
**div a1 a2 a3**            #Divide values in a1 and a2 and store the result in a3<br>
**addi a1 a2 number**       #Add value in a1 and number and store the result in a3<br>
**subi a1 a2 number**       #Sub value in a1 and number and store the result in a3<br>
**muli a1 a2 number**       #Multiply value in a1 and number and store the result in a3<br>
**divi a1 a2 number**       #Divide value in a1 and number and store the result in a3<br>
**LD a1 adr address**       #Load content stored at address into a1<br>
**ST a1 adr address**       #Store content of a1 into memory at addres<br>
<br><br>

We haven a 256 byte memory, of which bytes 0-127 are reserved for the executable and bytes 128 - 255 for load and store operations.
There are 8 registers: 7 genearal purpose register a1-a7 and one zero register x0.