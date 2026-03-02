#include <iostream>
#include <time.h>

#include "Strategy.h"

int main()
{
    //StrategyClient* client = new StrategyClient();
    //client->ClientCode();

    Object* object = new Object();
    object->AddProperty("name", "Bobby");
    object->AddProperty("age", "28");
    object->AddProperty("email", "bobby@mail.ru");
    object->AddProperty("city", "Moscow");

    for (int i{}; i < object->Size(); i++)
    {
        auto p = object->At(i);
        std::cout << p.first << ": " << p.second << "\n";
    }
    std::cout << "\n";

    object->ChangeProperty("age", "25");
    object->RemoveProperty("city");
    object->ChangeProperty("address", "Moscow");

    for (int i{}; i < object->Size(); i++)
    {
        auto p = object->At(i);
        std::cout << p.first << ": " << p.second << "\n";
    }
    std::cout << "\n";
}


