#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>

#include "Compiler.h"
#include "Memory.h"


Compiler::Compiler()
{
    positionInBinary = 0;
    compilerState = CompilerState::OK;
    return;
}

int Compiler::translateWord(std::string word, std::string& rlt)
{
    
    if(wordToHexMapping.count(word))
    {
        rlt = wordToHexMapping[word];
        compilerState = CompilerState::OK;
    }
    else if(!isNumeric(word))
    {
        compilerState = CompilerState::SyntaxError;
    }
    else
    {
        unsigned char wordAsNumber = std::stoi(word);
        std::stringstream numberAsStringStream;
        numberAsStringStream  << std::hex << +wordAsNumber;
        std::string hexCode = numberAsStringStream.str();
        if(hexCode.length() < 2)
        {
            hexCode.insert(0, 1, '0');
        }
        rlt = hexCode;
        compilerState = CompilerState::OK;
    }
    
    return compilerState;
};

int Compiler::getSize(std::string path)
{   
    std::ifstream file(path);
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

void Compiler::resetCompilerState()
{
    compilerState = CompilerState::OK;
    return;
}

int Compiler::compile(std::string name, Cpu* cpu, std::string rootPath)
{   
    int lineSize = 4;
    std::string binaryName = generateBinaryName(name);
    std::string pathToProgram = rootPath + "/programs/" + name;
    pathToBinary = rootPath + "/binaries/" + binaryName;

    cpu->registers.binaryPathRegister = pathToBinary;

    std::ofstream binary(pathToBinary);
    std::ifstream program(pathToProgram);
    
    std::string word;
    std::string binaryWord;

    int indexOfCurrentLine = 0;
    int indexOfCurrentWord =0;

    if(program.is_open() && binary.is_open())
    {
        while(program >> word)
        {   
            indexOfCurrentLine = (indexOfCurrentWord / lineSize) + 1;

            translateWord(word, binaryWord);
            if(compilerState == SyntaxError)
            {
                std::cout << "[ERROR] Syntax error in line " << indexOfCurrentLine << std::endl;
                std::cout << "The word " << word << " is invalid" << std::endl;
                program.close();
                binary.close();
                resetCompilerState();
                return 0;
            }
            binary << binaryWord;
            indexOfCurrentWord++;
        }
        
    }
    program.close();
    binary.close();
    resetCompilerState();
    return 1;
}

bool Compiler::isNumeric(std::string word)
{
    for(char const &c : word) 
    {
        if(std::isdigit(c) == 0)
        {
            return false;
        }
    }
    return true;
};

std::string Compiler::generateBinaryName(std::string programName)
{
    programName.pop_back();
    programName.append("hex");
    return programName;
}

void Compiler::resetPositinInBinary()
{
    positionInBinary = 0;
    return;
}
