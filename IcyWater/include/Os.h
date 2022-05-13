#include <vector>
#include <string>

#include "Compiler.h"
#include "Cpu.h"

class Os{
    private:
        Compiler compiler;
        //The root folder is IceWaterSystem
        std::string rootPath;
    
    public:

    private:
        void handleCpuStates(CpuState state);
        void printMenu(std::vector<std::string>& programNames);
        void chooseProgram(std::string& programName);
        void startProgram(std::string& name, Cpu* cpu);
        void getPrograms(std::vector<std::string>& programs);
        void clearConsole();
        bool doesProgramExist(std::string program, std::vector<std::string>& programs);
        bool continueRun();

    public:
        Os();
        void run(Cpu *cpu);
};