#include <iostream>
#include <vector>
#include <dirent.h>

#include "Cpu.h"
#include "memory.h"

void Cpu::RunProgram(std::string name)
{   
    int interpreter_state = interpreter.Run(name);
    if (interpreter_state == Interpreter::InterpreterState::SyntaxError)
    {
        std::cout << "\n[ERROR] Invalid programm" << std::endl;
        return;
    }
    int state = ControllUnit::State::OK;
    while(state == ControllUnit::State::OK)
    {
        cu.UpdateInstructionRegister();
        state = cu.ReadInstruction();
    }
    if(state = ControllUnit::State::DvisionByZero)
    {
        std::cout << "\n[ERROR] division by zero (core dumped)" << std::endl;
        
    }
    cu.ResetRegister();
}

void Cpu::Run()
{   
    int run = 1;
    while(run)
    {
        Clear();
        std::cout << "Icy Water: " << "\n\n" << std::endl;
        std::vector<std::string> names;
        std::string input;
        FindPrograms(names);
        std::cout << "Programmes: " << std::endl;
        for(const auto n : names)
        {
            std::cout << n << std::endl;
        }
        std::cout << "\nEnter name to run the program." << std::endl;
        std::cout << "Name: ";
        std::cin >> input;
        Clear();
        RunProgram(input);
        std::cout << "Continue [Y/N]?" << std::endl;
        std::cin >> input;
        if(input != "Y")
        {
            run = 0;
        }

    }
    
    
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
            names.push_back(diread->d_name);
        }
        closedir (dir);
    }
}


