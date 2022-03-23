#include <iostream>
#include "ComputingUnit.h"

#define PrintOp(op, a, b) std::cout << op << ": " << a << " and " << b << std::endl;  

unsigned char ComputingUnit::Add(unsigned char a, unsigned char b)
{
    unsigned char r;

    PrintOp("Add", +a, +b);
    r = a + b;
    std::cout << "Result: " << +r << "\n" << std::endl;
    return r;
    
}

unsigned char ComputingUnit::Sub(unsigned char a, unsigned char b)
{   
    unsigned char r;

    PrintOp("Sub", +a, +b);
    r = a - b;
    std::cout << "Result: " << +r << "\n" << std::endl;
    return r;
}

unsigned char ComputingUnit::Mul(unsigned char a, unsigned char b)
{   
    unsigned char r;

    PrintOp("Mul", +a, +b);
    r = a * b;
    std::cout << "Result: " << +r << "\n" << std::endl;
    return r;
}

unsigned char ComputingUnit::Div(unsigned char a, unsigned char b)
{   
    unsigned char r;

    PrintOp("Div", +a, +b);
    r = a / b;
    std::cout << "Result: " << +r << "\n" << std::endl;
    return r;
}