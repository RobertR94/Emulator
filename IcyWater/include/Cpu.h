#pragma once
#include <vector>
#include "Interpreter.h"
#include "ControllUnit.h"

class Cpu
{
    private:
        Interpreter interpreter;
        ControllUnit cu;

    public:


    private:
        bool PrintMenu(std::string& name);
        bool Continue();
        
    
    public:

       void RunProgram(std::string name);
       void Run();
       void Clear();
       void FindPrograms(std::vector<std::string>& names);
       bool InNames(std::string name, std::vector<std::string>& names);
       
};
