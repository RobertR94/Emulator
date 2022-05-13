#pragma once

#include <string>
#include <fstream>
#include <map>

#include "Memory.h"
#include "Cpu.h"

//Class to translate a assembler file into a binarie(.hex) file
//and write the binarie into memory
class Compiler
{   
    private:
        std::map<std::string, std::string> wordToHexMapping = {{"add", "00"}, {"sub", "01"}, {"mul", "02"}, {"div", "03"}, 
                                              {"addi", "04"}, {"subi", "05"}, {"muli", "06"}, {"divi", "07"},
                                              {"ST", "08"}, {"LD", "09"}, {"adr", "FF"}, 
                                              {"a1", "00"}, {"a2", "01"}, {"a3", "02"}, {"a4", "03"}, {"a5", "04"}, {"a6", "05"}, {"a6", "05"}, {"x0", "07"}};
        int positionInBinary;
        std::string pathToBinary;

    public:
        enum CompilerState
        {
            OK,
            SyntaxError
        };
        CompilerState compilerState;


    private:   
        //Translate assembler word into hex code
        int translateWord(std::string word, std::string& rlt);

        bool isNumeric(std::string word);

        int getSize(std::string file);

        std::string generateBinaryName(std::string programName);

        void resetCompilerState();

    public:
        Compiler();

        //Translate .S file into a binarie(.hex) file
        //Store the binary in the binaries folder
        int compile(std::string name, Cpu* cpu, std::string rootPath);
    
        void resetPositinInBinary();
};

