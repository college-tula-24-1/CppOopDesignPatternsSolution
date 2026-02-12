#include <iostream>

#include "ChainOfResponsibilityPattern.h"

int main()
{
    /*ConcreteHandlerA* handlerA = new ConcreteHandlerA();
    ConcreteHandlerB* handlerB = new ConcreteHandlerB();
    ConcreteHandlerC* handlerC = new ConcreteHandlerC();

    handlerA->SetNext(handlerB)->SetNext(handlerC);

    ChainClient* client = new ChainClient();
    client->ClientCode(handlerA);
    std::cout << "\n";*/

    PaymentHandler* payChain = new SberPaymentHandler();
    payChain->Push(new WesternUnionPaymentHandler());
    payChain->Push(new TBankPaymentHandler());

    PayRequest* request = new PayRequest(1000);
    payChain->PayHandle(request);
    std::cout << "\n";

    request->PayCheck(PayType::TBank);
    request->PayCheck(PayType::Sberbank);
    payChain->PayHandle(request);
    std::cout << "\n";

}


