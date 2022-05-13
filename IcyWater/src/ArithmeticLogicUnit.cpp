#include <iostream>
#include "ArithmeticLogicUnit.h"

#define printOperation(op, a, b) std::cout << op << ": " << a << " and " << b << std::endl;  

unsigned char ArithmeticLogicUnit::add(unsigned char a, unsigned char b)
{
    unsigned char result;

    printOperation("Add", +a, +b);
    result = a + b;
    std::cout << "Result: " << +result << "\n" << std::endl;
    return result;
    
}

unsigned char ArithmeticLogicUnit::sub(unsigned char a, unsigned char b)
{   
    unsigned char result;

    printOperation("Sub", +a, +b);
    result = a - b;
    std::cout << "Result: " << +result << "\n" << std::endl;
    return result;
}

unsigned char ArithmeticLogicUnit::mul(unsigned char a, unsigned char b)
{   
    unsigned char result;

    printOperation("Mul", +a, +b);
    result = a * b;
    std::cout << "Result: " << +result << "\n" << std::endl;
    return result;
}

unsigned char ArithmeticLogicUnit::div(unsigned char a, unsigned char b)
{   
    unsigned char result;

    printOperation("Div", +a, +b);
    result = a / b;
    std::cout << "Result: " << +result << "\n" << std::endl;
    return result;
}
