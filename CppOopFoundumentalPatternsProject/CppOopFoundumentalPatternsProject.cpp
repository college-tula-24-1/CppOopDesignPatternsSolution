#include <iostream>

#include "Examples.h"
#include "PropertyContainerPattern.cpp"


int main()
{
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
