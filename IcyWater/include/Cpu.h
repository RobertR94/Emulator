#pragma once /* Coderitter: Hier danach könnte dagegen noch eine Leerzeile hin. */
#include <vector>
#include "Interpreter.h"
#include "ControllUnit.h"

class Cpu
{
    private:
        Interpreter interpreter;
        /* Coderitter: Der Variablenname ist ein wenig kurz geraten. Der obendrüber 'interpreter' ist z.B. gut. */
        ControllUnit cu;

    public:
/* Coderitter: Zu viele Leerzeilen ;) */

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
