
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "Interpreter.h"
#include "memory.h"


int Interpreter::WordTranslate(std::string word, std::string& rlt)
{
    
    if(m.count(word))
    {
        rlt = m[word];
        return OK;
    }
    else if(!IsNumeric(word))
    {
        return SyntaxError;
    }
    
    unsigned char num = std::stoi(word);
    std::stringstream s;
    s  << std::hex << +num;
    std::string code = s.str();
    if(code.length() < 2)
    {
        code.insert(0, 1, '0');
    }
    rlt = code;
    return OK;
 
};


int Interpreter::WriteToMemory(std::string name)
{
    std::ifstream binary("/home/robert/MyProgramms/Challenge/Emulator/IcyWater/binaries/" + name);
    std::string w;
    std::stringstream stream;
    std::string l;
    int num;
    short cnt = 0;
    unsigned char n;

    if(binary.is_open()){
        while(binary >> w)
        {
            for(int b = 0; b < w.length(); b+=2)
            {   
                l = w.substr(b, 2);
                stream << std::hex << l;
                stream >> num;
                n = (unsigned char) num;
                
                if(cnt >= 128)
                {

                }
                                   
                memory[cnt] = n;
                
                cnt++;
                stream.str("");
                stream.clear();
            }
        };
        for(int i = 0; i < 4; i++){
            memory[cnt + i] = 0xFF;
        }
    }
    binary.close();
    return OK;
}


int Interpreter::ToBinary(std::string name, std::string& b_name)
{   
    b_name = name + ".hex";
    std::ofstream binary("/home/robert/MyProgramms/Challenge/Emulator/IcyWater/binaries/" + b_name);
    
    std::ifstream program("/home/robert/MyProgramms/Challenge/Emulator/IcyWater/programs/" + name);
    std::string w;
    std::vector<std::string> slp;
    std::string word;
    int state;

    if(program.is_open() && binary.is_open())
    {
        while (program >> w)
        {   
            state = WordTranslate(w, word);
            if(state == SyntaxError)
            {
                return state;
            }
            binary << word;
        }
        
    }
    program.close();
    binary.close();
    return state;
}

bool Interpreter::IsNumeric(std::string s)
{
    for (char const &c : s) 
    {
        if (std::isdigit(c) == 0)
        {
            return false;
        }
    }
    return true;
};


int Interpreter::Run(std::string name)
{
    std::string b_name;
    int binary_state, memory_state;
    binary_state = ToBinary(name, b_name);
    if(binary_state == SyntaxError)
    {
        return SyntaxError;
    }

    return WriteToMemory(b_name);

};





