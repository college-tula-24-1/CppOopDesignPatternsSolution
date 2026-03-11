#include <iostream>
#include <time.h>

#include "Visitor.h"


int main()
{
    //VisitorClient* client = new VisitorClient();
    //client->ClientCode();

    Bank* bank = new Bank();
    
    Person* bobby = new Person();
    bobby->Name() = "Bobby";
    bobby->Number() = "AD_12345";
    bobby->Amount() = 250000;
    bank->Add(bobby);

    Company* yandex = new Company();
    yandex->Title() = "Yandex";
    yandex->Number() = "TWE 16235344 90 PL";
    yandex->License() = "ASC-000012346";
    yandex->Amount() = 12678000;
    bank->Add(yandex);

    bank->AcceptAll(new JsonVisitor());
    bank->AcceptAll(new XmlVisitor());
}


