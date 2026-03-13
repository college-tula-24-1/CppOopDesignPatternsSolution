#include <iostream>
#include <time.h>

#include "RomanNumbers.h"

int main()
{
    RNInterpreter* interpreter = new RNInterpreter();
    std::string rn{ "MMMM" }; // 1996, 3999

    std::cout << rn << " is " << interpreter->Interpret(rn);
}


