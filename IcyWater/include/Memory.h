#pragma once

#include<iostream>

class Memory{

    private:

    public:
        unsigned char mem[256];
        unsigned char bound = 127;
    
    private:

    public:
        Memory();
        int getFileSize(std::string path);
        void loadBinaryIntoMemory(std::string pathToBinary, int& positionInBinary);
};