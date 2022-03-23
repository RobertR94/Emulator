#include <iostream>
#include <vector>
#include <dirent.h>
#include <cstring>

#include "memory.h"
#include "Cpu.h"

void Cpu::RunProgram(std::string name)
{   
    cu.ResetGPRegister();
    cu.RestControllRegister();
    interpreter.ResetFilePos();
    int interpreter_state = interpreter.ToBinary(name);

    if (interpreter_state == Interpreter::InterpreterState::SyntaxError)
    {
        std::cout << "\n[ERROR] Invalid programm" << std::endl;
        return;
    }

    interpreter.WriteToMemory();
    int controll_unit_state = ControllUnit::OK;  

    while(controll_unit_state == ControllUnit::OK)
    {   
        controll_unit_state = cu.UpdateInstructionRegister();
        if(controll_unit_state == ControllUnit::OutOfMemory)
        {
            cu.RestControllRegister();
            interpreter.WriteToMemory();
            controll_unit_state = cu.UpdateInstructionRegister();
        }
        controll_unit_state = cu.ReadInstruction();
        
    }
    
    if(controll_unit_state == ControllUnit::State::DvisionByZero)
    {
        std::cout << "\n[ERROR] division by zero (core dumped)" << std::endl;
        
    }
    return;
}

bool Cpu::InNames(std::string name, std::vector<std::string>& names)
{
    for(auto n : names)
    {
        if(n.compare(name) == 0)
        {
            return true;
        }
    }
    return false;
}


bool Cpu::PrintMenu(std::string& name)
{
    while(1)
    {
        std::vector<std::string> names;
        std::string input;

        Clear();
        FindPrograms(names);

        std::cout << "Icy Water: " << "\n\n" << std::endl;
        std::cout << "Programmes: " << std::endl;
        for(const auto n : names)
        {
            std::cout << n << std::endl;
        }
        std::cout << "\nEnter name to run the program." << std::endl;
        std::cin >> name;
        if(InNames(name, names))
        {
            return true;
        }
        std::cout << "\n" << std::endl;
        std::cout << "Program not found!";
        std::cout << "Continue [Y/N]?" << std::endl;
        std::cin >> input;
        if(input.compare("Y") != 0)
        {
            return false;
        }
    }
}


bool Cpu::Continue()
{       
        std::string input;
        std::cout << "\nContinue [Y/N]?" << std::endl;
        std::cin >> input;
        if(input == "Y")
        {
            return true;
        }
        return false;
}


void Cpu::Run()
{   
    std::string name;
    int run =  true;    
    while(run == true)
    {
        
        if(PrintMenu(name))
        {
            RunProgram(name);
            run = Continue();
        }
        else
        {
            return;
        }

    }
    return;
    
}

void Cpu::Clear()
{
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}



void Cpu::FindPrograms(std::vector<std::string>& names)
{   
    DIR *dir; struct dirent *diread;
    

    if ((dir = opendir("/home/robert/MyProgramms/Challenge/Emulator/IcyWater/programs")) != nullptr) 
    {   
    
        while ((diread = readdir(dir)) != nullptr) 
        {
            if(strcmp(diread->d_name, ".") != 0 && strcmp(diread->d_name, "..") != 0)
            {
                names.push_back(diread->d_name);
            }
        }
        closedir (dir);
    }
}


