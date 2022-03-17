#pragma once
#include "Interpreter.h"
#include "ControllUnit.h"

class Cpu
{
    private:
        Interpreter interpreter;
        ControllUnit cu;
        
    
    public:

       void RunProgram(std::string name);
       void Run();
       void Clear();
       void FindPrograms(std::vector<std::string>& names);
       
};
