#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <map>

class Observer
{
	std::string name;
public:
	Observer(std::string name) : name{ name }{}
	virtual ~Observer() = default;

	virtual void EventHandler(std::string stateObservable) = 0;
	std::string Name() const { return this->name; }
};

class Observable
{
public:
	virtual ~Observable() = default;
	virtual void AddObserver(Observer* observer) = 0;
	virtual void RemoveObserver(Observer* observer) = 0;
	virtual void NotifyObservers() = 0;
};

class ConcreteObservable : public Observable
{
	std::list<Observer*> observers;
	std::string state;

	std::string GenerateRandomState(int length = 20)
	{
		const char alphaNumbers[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		int alphaNumbersLength = sizeof(alphaNumbers) - 1;

		std::string randomState = "";
		for (int i{}; i < length; i++)
			randomState += alphaNumbers[std::rand() % alphaNumbersLength];

		return randomState;
	}
public:
	void AddObserver(Observer* observer) override
	{
		std::cout << "Observable. Add new observer: " << observer->Name() << "\n";
		observers.push_back(observer);
	}

	void RemoveObserver(Observer* observer) override
	{
		std::cout << "Observable. Remove observer: " << observer->Name() << "\n";
		observers.remove(observer);
	}

	void NotifyObservers() override
	{
		std::cout << "Observable. Notify my obeservers.\n";
		for (auto observer : observers)
			observer->EventHandler(state);
	}

	void BuisnessLogic()
	{
		this->state = this->GenerateRandomState();
		std::cout << "Observable. Change state: " << this->state << "\n";
		this->NotifyObservers();
	}
};

class ConcreteObserver : public Observer
{
	std::string state;
	Observable* observable;
public:
	ConcreteObserver(std::string name, Observable* observable = nullptr) 
		: Observer(name), observable{ observable }
	{
		if (observable)
			this->Attach(observable);
	}

	void EventHandler(std::string stateObservable)
	{
		std::cout << "Observer " << this->Name() << ". Handled event from Observable\n";
		this->state = stateObservable;
		std::cout << "\t New Observable state: " << stateObservable << "\n";
	}

	void Attach(Observable* observable)
	{
		std::cout << "Observer " << this->Name() << ". Attach to Observable\n";
		this->observable = observable;

		this->observable->AddObserver(this);
	}

	void Detach()
	{
		std::cout << "Observer " << this->Name() << ". Detach from Observable\n";
		this->observable->RemoveObserver(this);
	}
};

class ObserverClient
{
public:
	void ClientCode()
	{
		ConcreteObservable* observable = new ConcreteObservable();

		ConcreteObserver* observerA = new ConcreteObserver("Observer A");
		observerA->Attach(observable);

		ConcreteObserver* observerB = new ConcreteObserver("Observer B", observable);

		observable->BuisnessLogic();
	}
};

///

class MarketInfo
{
	int usd;
	int euro;
public:
	MarketInfo() : usd{}, euro{}{}

	int& Usd() { return this->usd; }
	int& Euro() { return this->euro; }
};

class MarketObserver;

class MarketObservable
{
public:
	virtual void AddObserver(MarketObserver* observer) = 0;
	virtual void RemoveObserver(MarketObserver* observer) = 0;
	virtual void NotifyObservers() = 0;
};

class MarketObserver
{
protected:
	std::string name;
	MarketObservable* market;
	int levelUsd;
	int levelEuro;
public:
	MarketObserver(std::string name,
		int levelUsd,
		int levelEuro,
		MarketObservable* market = nullptr) 
		: name{ name }, 
		levelUsd{ levelUsd },
		levelEuro{ levelEuro },
		market{ market }
	{
		if (market)
		{
			market->AddObserver(this);
			std::cout << name << " add to market\n";
		}
			
	}

	virtual void MarketEventHandler(MarketInfo* info) = 0;
	std::string Name() const { return this->name; }
};

class Market : public MarketObservable
{
	MarketInfo* info;
	std::list<MarketObserver*> clients;
public:
	Market() : info{ new MarketInfo() }{}

	void AddObserver(MarketObserver* client) override
	{
		clients.push_back(client);
		std::cout << "Market add new client " << client->Name() <<"\n";
	}
	void RemoveObserver(MarketObserver* client) override
	{
		clients.remove(client);
		std::cout << "Market remove client " << client->Name() << "\n";
	}
	void NotifyObservers()
	{
		std::cout << "Market notify clients.\n";
		for (auto client : clients)
			client->MarketEventHandler(info);
	}

	void StockTrading()
	{
		this->info->Usd() = 70 + rand() % 21;
		this->info->Euro() = 80 + rand() % 11;

		std::cout << "Market Trading:\n";
		std::cout << "\tUsd: " << this->info->Usd() << "\n";
		std::cout << "\tEuro: " << this->info->Euro() << "\n";

		this->NotifyObservers();
	}
};

class BrokerUsd : public MarketObserver
{
public:
	BrokerUsd(int levelUsd, int levelEuro, MarketObservable* market)
		: MarketObserver("Broker Usd", levelUsd, levelEuro, market){ }
	void MarketEventHandler(MarketInfo* info) override
	{
		if (info->Usd() <= levelUsd)
			std::cout << name << " byed usd at " << info->Usd() << "\n";
		else
			std::cout << name << " saled usd at " << info->Usd() << "\n";
	}
};

class BrokerEuro : public MarketObserver
{
public:
	BrokerEuro(int levelUsd, int levelEuro, MarketObservable* market)
		: MarketObserver("Broker Euro", levelUsd, levelEuro, market) {
	}
	void MarketEventHandler(MarketInfo* info) override
	{
		if (info->Euro() <= levelEuro)
			std::cout << name << " byed euro at " << info->Euro() << "\n";
		else
			std::cout << name << " saled euro at " << info->Euro() << "\n";
	}
};

class Broker : public MarketObserver
{
public:
	Broker(int levelUsd, int levelEuro, MarketObservable* market)
		: MarketObserver("Broker Universul", levelUsd, levelEuro, market) {
	}
	void MarketEventHandler(MarketInfo* info) override
	{
		if (info->Usd() <= levelUsd)
			std::cout << name << " byed usd at " << info->Usd() << "\n";
		else
			std::cout << name << " saled usd at " << info->Usd() << "\n";

		if (info->Euro() <= levelEuro)
			std::cout << name << " byed euro at " << info->Euro() << "\n";
		else
			std::cout << name << " saled euro at " << info->Euro() << "\n";
	}
};

class Bank : public MarketObserver
{
public:
	Bank(int levelUsd, int levelEuro, MarketObservable* market)
		: MarketObserver("Bank", levelUsd, levelEuro, market) {
	}
	void MarketEventHandler(MarketInfo* info) override
	{
		if (info->Usd() > levelUsd)
			std::cout << name << " saled usd at " << info->Usd() << "\n";

		if (info->Euro() > levelEuro)
			std::cout << name << " saled euro at " << info->Euro() << "\n";
	}
};

class Buisness
{
public:
	void BuisnessTrading()
	{
		int rounds{ 5 };
		Market* market = new Market();
		BrokerUsd* brokerUsd = new BrokerUsd(78, 82, market);
		BrokerEuro* brokerEuro = new BrokerEuro(78, 85, market);
		Broker* broker = new Broker(80, 84, market);
		Bank* bank = new Bank(81, 86, market);

		for (int i{}; i < rounds; i++)
		{
			market->StockTrading();
		}
	}
};
