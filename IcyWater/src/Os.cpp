#include <iostream>
#include <dirent.h>
#include <cstring>
#include <filesystem>

#include "Os.h"


Os::Os()
{
    std::string currentPath = std::filesystem::current_path();
    std::string pathToParentFolder = currentPath.substr(0, currentPath.find_last_of("/EMULATOR"));
    std::cout << pathToParentFolder << std::endl;
    rootPath = pathToParentFolder + "/IceWaterSystem";

    return;
}

bool Os::doesProgramExist(std::string program, std::vector<std::string>& programs)
{
    for(auto p : programs)
    {
        if(p.compare(program) == 0)
        {
            return true;
        }
    }
    return false;
}

void Os::printMenu(std::vector<std::string>& programNames)
{  
    std::string input;

    clearConsole();

    std::cout << "Ice Water: " << "\n\n" << std::endl;
    std::cout << "Programmes: " << std::endl;
    for(const auto n : programNames)
    {
        std::cout << "ha: " << n << std::endl;
    }
    std::cout << "\nEnter a name to run the program." << std::endl;  

    return;
}

void Os::chooseProgram(std::string& programName)
{      
    std::cin >> programName;
    std::cout << std::endl; 
    return;
}

bool Os::continueRun()
{       
    std::string input;
    std::cout << "\nContinue [Y/N]?" << std::endl;
    std::cin >> input;
    if(input == "Y" || input == "y")
    {
        return true;
    }
    return false;
}

void Os::clearConsole()
{
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif

    return;
}

void Os::getPrograms(std::vector<std::string>& names)
{   

    DIR *dir; struct dirent *diread; 
    std::string systemPath = rootPath + "/programs";

    const char* path = systemPath.c_str();
    
    if((dir = opendir(path)) != nullptr) 
    {   
        while((diread = readdir(dir)) != nullptr) 
        {
            if(strcmp(diread->d_name, ".") != 0 && strcmp(diread->d_name, "..") != 0)
            {
                names.push_back(diread->d_name);
            }
        }
        closedir (dir);
    }
    return;
}

void Os::handleCpuStates(CpuState state)
{
    switch (state)
    {
    case CpuState::OK:
        std::cout << "[ERROR] The program was interrupted" << std::endl;
        return;
    
    case CpuState::Exit:
        return;       
        
    case CpuState::Invalid:
        std::cout << "[ERROR] The program is invalid" << std::endl;
        return;
    
    case CpuState::DvisionByZero:
        std::cout << "[ERROR] Division by Zero" << std::endl;
        return;

    case CpuState::MemoryFault:
        std::cout << "[ERROR] invalid memory access";
        return;

    default:
       return;
    }
}

void Os::startProgram(std::string& name, Cpu* cpu)
{
    int compileSucces;
    compileSucces = compiler.compile(name, cpu, rootPath);
    if(compileSucces)
    {
        CpuState cpuState = cpu->runProgram(name);
        handleCpuStates(cpuState);
    }
    return;
}


void Os::run(Cpu* cpu)
{
    std::string programName;
    std::vector<std::string> programNames;
    int state;

    getPrograms(programNames);

    int run =  true; 
    while(run == true)
    {
        printMenu(programNames);
        chooseProgram(programName);
        if(doesProgramExist(programName ,programNames))
        {   
            startProgram(programName, cpu);
        }
        else
        {
            std::cout << " [ERROR] The choosen program does not exist." << std::endl;
        }
        run = continueRun();
    }
    
    return;
}
