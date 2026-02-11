#include <iostream>

#include "ChainOfResponsibilityPattern.h"

int main()
{
    ConcreteHandlerA* handlerA = new ConcreteHandlerA();
    ConcreteHandlerB* handlerB = new ConcreteHandlerB();
    ConcreteHandlerC* handlerC = new ConcreteHandlerC();

    handlerA->SetNext(handlerB)->SetNext(handlerC);

    ChainClient* client = new ChainClient();
    client->ClientCode(handlerA);
    std::cout << "\n";
}


