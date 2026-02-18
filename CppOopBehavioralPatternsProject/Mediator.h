#pragma once
#include <iostream>

class Component;
class IMediator
{
public:
	virtual void Notify(Component* componenet, std::string event) = 0;
};

class Component
{
protected:
	IMediator* mediator;
public:
	Component(IMediator* mediator = nullptr) : mediator{ mediator } {}

	void SetMediator(IMediator* mediator) { this->mediator = mediator; }
};

class ComponentA : public Component
{
public:
	void EventOne()
	{
		std::cout << "Component A event One\n";
		mediator->Notify(this, "EventOne");
	}

	void EventTwo()
	{
		std::cout << "Component A event Two\n";
		mediator->Notify(this, "EventTwo");
	}
};

class ComponentB : public Component
{
public:
	void EventOne()
	{
		std::cout << "Component B event One\n";
		mediator->Notify(this, "EventOne");
	}

	void EventThree()
	{
		std::cout << "Component B event Three\n";
		mediator->Notify(this, "EventThree");
	}
};

class ComponentC : public Component
{
public:
	void EventTwo()
	{
		std::cout << "Component C event Two\n";
		mediator->Notify(this, "EventTwo");
	}

	void EventThree()
	{
		std::cout << "Component B event Three\n";
		mediator->Notify(this, "EventThree");
	}
};


class ConcreteMediator : public IMediator
{
	ComponentA* componenetA;
	ComponentB* componenetB;
	ComponentC* componenetC;
public:
	ConcreteMediator(ComponentA* componenetA, 
		ComponentB* componenetB,
		ComponentC* componenetC)
		: componenetA{ componenetA }, 
		componenetB{ componenetB },
		componenetC{ componenetC }
	{
		componenetA->SetMediator(this);
		componenetB->SetMediator(this);
		componenetC->SetMediator(this);
	}

	void Notify(Component* componenet, std::string event) override
	{
		if (event == "EventOne")
		{
			std::cout << "Event One\n";
			componenetB->EventOne();
			
		}
		else if (event == "EventTwo")
		{
			std::cout << "Event Two\n";
			componenetA->EventTwo();
			componenetC->EventTwo();
		}
		else if (event == "EventThree")
		{
			std::cout << "Event Three\n";
			componenetB->EventThree();
			componenetC->EventThree();
		}
	}

};


///
enum class CollegueType
{
	Customer,
	Developer,
	Tester
};

class Collegue; // Component
class IManager   // Mediator
{
public:
	virtual void SendOrder(Collegue* collegue, std::string message) = 0;
};

class Collegue
{
	IManager* manager;
	CollegueType type;
public:
	Collegue(CollegueType type, IManager* manager = nullptr)
		: manager{ manager }, type{ type }{ }

	virtual void SendMessage(std::string message)
	{
		manager->SendOrder(this, message);
	}

	void SetManager(IManager* manager) { this->manager = manager; }

	CollegueType Type() { return type; }

	virtual void Notify(std::string message) = 0;
};

class CustomerCollegue : public Collegue
{
public:
	CustomerCollegue(IManager* manager = nullptr)
		: Collegue(CollegueType::Customer, manager){ }
	
	void Notify(std::string message) override
	{
		std::cout << "Message for Customer: " << message << "\n";
	}
};

class DeveloperCollegue : public Collegue
{
public:
	DeveloperCollegue(IManager* manager = nullptr)
		: Collegue(CollegueType::Developer, manager) {
	}

	void Notify(std::string message) override
	{
		std::cout << "Message for Developer: " << message << "\n";
	}
};

class TesterCollegue : public Collegue
{
public:
	TesterCollegue(IManager* manager = nullptr)
		: Collegue(CollegueType::Tester, manager) {
	}

	void Notify(std::string message) override
	{
		std::cout << "Message for Tester: " << message << "\n";
	}
};

class Manager : public IManager
{
	Collegue* customer;
	Collegue* developer;
	Collegue* tester;
public:
	Manager(Collegue* customer,
	Collegue* developer,
	Collegue* tester) 
		: customer{ customer },
		developer{ developer },
		tester{ tester }{ }

	void SendOrder(Collegue* collegue, std::string message)
	{
		if (collegue->Type() == CollegueType::Customer)
		{
			developer->Notify(message);
		}

		if (collegue->Type() == CollegueType::Developer)
		{
			tester->Notify(message);
		}

		if (collegue->Type() == CollegueType::Tester)
		{
			customer->Notify(message);
		}
	}
};

class Company
{
public:
	void Work()
	{
		Collegue* customer = new CustomerCollegue();
		Collegue* developer = new DeveloperCollegue();
		Collegue* tester = new TesterCollegue();

		Manager* manager = new Manager(customer, developer, tester);
		customer->SetManager(manager);
		developer->SetManager(manager);
		tester->SetManager(manager);

		customer->SendMessage("Order! I need of Programm!");
		developer->SendMessage("Ok. Program is Ready!");
		tester->SendMessage("Ok. Program Ready and Tested");
	}
};