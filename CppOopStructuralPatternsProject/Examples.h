#pragma once
#include "Adapter.h"
using namespace AdapterNamespace;

#include "Bridge.h"
using namespace BridgeNamespace;

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

	static void BrudgeExample()
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
};

