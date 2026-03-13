#include <iostream>
#include <time.h>
#include <map>

#include "RomanNumbers.h"

int RomanToDecimal(std::string& input);

int main()
{
    RNInterpreter* interpreter = new RNInterpreter();
    std::string rn{ "MCMXCVI" }; // 1996, 3999

    std::cout << rn << " is " << interpreter->Interpret(rn) << "\n";
    std::cout << rn << " is " << RomanToDecimal(rn) << "\n";
}

int RomanToDecimal(std::string& input)
{
    std::map<char, int> romanDigit;
    romanDigit.insert(std::make_pair('I', 1));
    romanDigit.insert(std::make_pair('V', 5));
    romanDigit.insert(std::make_pair('X', 10));
    romanDigit.insert(std::make_pair('L', 50));
    romanDigit.insert(std::make_pair('C', 100));
    romanDigit.insert(std::make_pair('D', 500));
    romanDigit.insert(std::make_pair('M', 1000));

    int result{};
    for (int i{}; i < input.length(); i++)
    {
        if (romanDigit[input[i]] < romanDigit[input[i + 1]])
        {
            result += romanDigit[input[i + 1]] - romanDigit[input[i]];
            i++;
            continue;
        }
        result += romanDigit[input[i]];
    }
    return result;
}
