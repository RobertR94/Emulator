#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <map>

//Class to translate a assembler file into a binarie(.hex) file
//and write the binarie into memory
class Interpreter
{   

    public:
        enum InterpreterState
        {
            OK,
            SyntaxError
        };

    private:

       std::map<std::string, std::string> m = {{"add", "00"}, {"sub", "01"}, {"mul", "02"}, {"div", "03"}, 
                                              {"addi", "04"}, {"subi", "05"}, {"muli", "06"}, {"divi", "07"},
                                              {"ST", "08"}, {"LD", "09"}, {"adr", "FF"}, 
                                              {"a1", "00"}, {"a2", "01"}, {"a3", "02"}, {"a4", "03"}, {"a5", "04"}, {"a6", "05"}, {"a6", "05"}, {"x0", "07"}}; 

        unsigned char* mem_p = NULL;

    public:
        int Run(std::string name);

       

    

    private:

        //Translate .S file into a binarie(.hex) file
        //Store the binary in the binaries folder
        int ToBinary(std::string name, std::string& b_name);
        //Write binary(hex) instruction into the memory
        int WriteToMemory(std::string name);
        //Translate assembler word into hex code
        int WordTranslate(std::string word, std::string& rlt);

        bool IsNumeric(std::string s);


        
};

