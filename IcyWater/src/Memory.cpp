#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

#include "Memory.h"

Memory::Memory(){
    std::fill(mem, mem+256, 0b00000000);
};

int Memory::getFileSize(std::string pathToFile)
{   
    std::ifstream file(pathToFile);
    std::string line;
    int size = 0;

    if(file.is_open())
    {
        while(file >> line)
        {
            size += line.size();
        }
    }
    file.close();

    return size;
}

void Memory::loadBinaryIntoMemory(std::string pathToBinary, int& positionInBinary)
{
    //part of the binary that we can load into the memory
    //max 128 byte, hence 256 characters
    std::string contentSlice;

    std::string byteAsHexString;
    std::stringstream hexStringStream;

    int hexStringAsDecimalNumber, lengthOfContentSlice;
    unsigned char hexCode;
    unsigned char currentAddress = 0;

    lengthOfContentSlice = std::min((getFileSize(pathToBinary) - positionInBinary), (128)*2);
    std::ifstream binary(pathToBinary);;
    if(binary.is_open())
    {    
        binary.seekg(positionInBinary, std::ios::beg);
        contentSlice.resize(lengthOfContentSlice);
        binary.read(&contentSlice[0], lengthOfContentSlice);
        int positionInContentSlice = 0;
        
        while(currentAddress <= bound)
        {
            if(positionInContentSlice < contentSlice.size())
            {
                byteAsHexString = contentSlice.substr(positionInContentSlice, 2);
                hexStringStream << std::hex << byteAsHexString;
                hexStringStream >> hexStringAsDecimalNumber;
                hexCode = (unsigned char) hexStringAsDecimalNumber;
                mem[currentAddress] = hexCode;
                hexStringStream.str("");
                hexStringStream.clear();
                positionInContentSlice += 2;
           
            }
            else
            {
                if(currentAddress <= (bound - 3))
                {
                    
                    mem[currentAddress + 0] = 0xFF;
                    mem[currentAddress + 1] = 0xFF;
                    mem[currentAddress + 2] = 0xFF;
                    mem[currentAddress + 3] = 0xFF;
                    
                }
                return;
            }
            currentAddress++;
            positionInBinary += 2;
        }  
    } 

    binary.close();
    return;
}
