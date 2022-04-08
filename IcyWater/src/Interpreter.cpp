
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

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


int Interpreter::GetSize(std::string path)
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



void Interpreter::WriteToMemory()
{

    std::string s;
    std::string byte;
    std::stringstream stream;
    int num, length;
    unsigned char hex;
    unsigned char address = 0;
    length = std::min((GetSize(binary_path) - file_pos), (128)*2);
    std::ifstream binary(binary_path);

    if(binary.is_open())
    {   
        
        binary.seekg(file_pos, std::ios::beg);
        s.resize(length);
        binary.read(&s[0], length);
        int sub_start = 0;

        while(address <= 127)
        {
            if(sub_start < s.size())
            {
                byte = s.substr(sub_start, 2);
                stream << std::hex << byte;
                stream >> num;
                hex = (unsigned char) num;
                memory[address] = hex;
                stream.str("");
                stream.clear();
                sub_start += 2;
           
            }
            else
            {
                if(address <= (127 - 4))
                {
                    for(int i = 0; i < 4; i++)
                    {
                        memory[address + i] = 0xFF;
                    }
                    
                }
                return;
            }
            address++;
            file_pos += 2;
        }  
    } 

    binary.close();
}




int Interpreter::ToBinary(std::string name)
{   
    binary_path = NameBinary(name);
    std::ofstream binary(binary_path);
    
    std::ifstream program("/home/robert/MyProgramms/Challenge/Emulator/IcyWater/programs/" + name);
    std::string w;
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


std::string Interpreter::NameBinary(std::string s)
{
    s.pop_back();
    s.append("hex");
    return "/home/robert/MyProgramms/Challenge/Emulator/IcyWater/binaries/" + s;
}


void Interpreter::ResetFilePos()
{
    file_pos = 0;
}






