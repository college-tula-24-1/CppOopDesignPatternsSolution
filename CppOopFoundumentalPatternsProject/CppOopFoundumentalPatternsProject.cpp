#include <iostream>

#include "Examples.h"
#include "PropertyContainerPattern.cpp"

class Employee
{
    std::string name;
    int age;
public:
    Employee(std::string name = "", int age = 0)
        : name{ name }, age{ age }{}
};

class Company
{
    Employee* employees = new Employee[10];
};


int main()
{
    Employee manager("Bobby", 25);

    Movie warAndPiece;
    warAndPiece.Title() = "War and Peice";

    warAndPiece.SetProperty("country", "USSR");
    warAndPiece.SetProperty("year", "1965");
    warAndPiece.SetProperty("director", "S. Bondarchuk");

    std::cout << warAndPiece.Id() << " " << warAndPiece.Title() << "\n";
    
    auto properties = warAndPiece.GetPropertyNames();

    for (auto it{ properties.begin() }; it != properties.end(); it++)
        std::cout << *it << ": " << warAndPiece.GetProperty(*it) << "\n";
}
