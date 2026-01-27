#pragma once
#include "Adapter.h"
using namespace AdapterNamespace;

#include "Bridge.h"
using namespace BridgeNamespace;

#include "Composite.h"
using namespace ComponenetNamespace;

#include "Decorator.h"
using namespace DecoratorNamespace;

#include "Facade.h"
using namespace FacadeNamespace;

class Examples
{
public:
	static void AdapterExamples()
	{
        AdapterNamespace::Client* client = new AdapterNamespace::Client();
		client->ClientCode(new ConcreteClassA());
		client->ClientCode(new ConcreteClassB());

		client->ClientCode(new ServiceAdapter(new Service(), 500));
	}

	static void BridgeExamples()
	{
        BridgeNamespace::Client* client = new BridgeNamespace::Client();

        Implementation* implementor = new ConcreteImplementationA();
        Abstraction* abstraction = new Abstraction(implementor);

        client->ClientCode(abstraction);
        delete implementor;
        delete abstraction;
        client->ClientCode(new Abstraction(new ConcreteImplementationB()));
        abstraction = new ExtendedAbstraction(new ConcreteImplementationA());
        client->ClientCode(abstraction);

        //Logger* logger = new SimpleThreadLogger(new ConsoleLogger());
        Logger* logger = new SimpleThreadLogger(new FileLogger("file01.log"));
        System system(logger);
        system.Work();
	}

    static void CompositeExamples()
    {
        /*Client* client = new Client();
    client->ClientCode();*/

        Army* army = new Army();
        army->CreateArmy();
        army->Info();
    }
    
    static void DecoratorExamples()
    {
        /*Client* client = new Client();

        Component* simpleComponenet = new ConcreteComponenet();
        client->ClientCode(simpleComponenet);

        Component* decorator1 = new ConcreteDecoratorB(simpleComponenet);
        client->ClientCode(decorator1);

        Component* decorator2 = new ConcreteDecoratorA(decorator1);
        client->ClientCode(decorator2);

        delete simpleComponenet;
        delete decorator1;
        delete decorator2;*/

        MessageClient* client = new MessageClient();

        IMessage* message = new MessangerMessage();
        message->From() = "#Bob";
        message->To() = "#Joe";
        message->Text() = "Hello world";
        client->SendMessage(message);
        std::cout << "\n";

        message = new FileMessage(message, "photo.jpg");
        client->SendMessage(message);
        std::cout << "\n";

        message = new ContactMessage(message, "Leo: (900) 123-45-67");
        client->SendMessage(message);
        std::cout << "\n";
    }

    static void FacadeExamples()
    {
        /*Facade* facade = new Facade(new SubsystemA());
        FacadeClient* client = new FacadeClient();
        client->ClientCode(facade);*/

        Programmer* programmer = new Programmer();
        programmer->CreateApplication(
            new Ide(new TextEditor(),
                new Compiller(),
                new RuntimeEnvironment()));
    }


};

