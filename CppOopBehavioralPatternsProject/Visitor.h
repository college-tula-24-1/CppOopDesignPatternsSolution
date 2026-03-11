#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Element;

class Visitor
{
public:
	virtual void Visit(const Element* element) = 0;
};

class Element
{
public:
	virtual ~Element() = default;

	virtual void Accept(Visitor* visitor) = 0;
};

class ConcreteElementA : public Element
{
public:
	void Accept(Visitor* visitor) override
	{
		visitor->Visit(this);
	}

	void BuisnessLogicA()
	{
		std::cout << "Concrete Element A Buisness Logic\n";
	}
};

class ConcreteElementB : public Element
{
public:
	void Accept(Visitor* visitor) override
	{
		visitor->Visit(this);
	}

	void BuisnessLogicB()
	{
		std::cout << "Concrete Element B Buisness Logic\n";
	}
};

class ConcreteVisitorA : public Visitor
{
public:
	void Visit(const Element* element) override
	{
		auto elementA = (ConcreteElementA*)element;
		
		std::cout << "Concrete Visitor A visit Element A\n";
		elementA->BuisnessLogicA();
		
	}
};

class ConcreteVisitorB : public Visitor
{
public:
	void Visit(const Element* element) override
	{
		auto elementB = (ConcreteElementB*)element;

		std::cout << "Concrete Visitor B visit Element B\n";
		elementB->BuisnessLogicB();
	}
};

class VisitorClient
{
public:
	void VisitToElement(Element* element, Visitor* visitor)
	{
		element->Accept(visitor);
	}

	void ClientCode()
	{
		VisitToElement(new ConcreteElementA(), new ConcreteVisitorA);
		VisitToElement(new ConcreteElementB(), new ConcreteVisitorB);
	}
};

//

class IClient;
class Person;
class Company;

class IVisitor
{
public:
	virtual void VisitPerson(Person* client) = 0;
	virtual void VisitCompany(Company* client) = 0;
};

class IClient
{
public:
	virtual void Accept(IVisitor* visitor) = 0;
};

class Person : public IClient
{
	std::string name;
	std::string number;
	int amount;
public:
	std::string& Name() { return this->name; }
	std::string& Number() { return this->number; }
	int& Amount() { return this->amount; }

	void Accept(IVisitor* visitor) override
	{
		visitor->VisitPerson(this);
	}

};

class Company : public IClient
{
	std::string title;
	std::string number;
	std::string license;
	int amount;
public:
	std::string& Title() { return this->title; }
	std::string& Number() { return this->number; }
	std::string& License() { return this->license; }
	int& Amount() { return this->amount; }

	void Accept(IVisitor* visitor) override
	{
		visitor->VisitCompany(this);
	}
};

class Bank
{
	std::vector<IClient*> clients;
public:
	void Add(IClient* client)
	{
		clients.push_back(client);
	}

	void Remove(int index)
	{
		clients.erase(clients.begin() + index);
	}

	void AcceptAll(IVisitor* visitor)
	{
		for (auto client : clients)
			client->Accept(visitor);
	}
};

class XmlVisitor : public IVisitor
{
public:
	void VisitPerson(Person* client) override
	{
		std::string result = "<person>\n";
		result += "\t<name>" + client->Name() + "</name>\n";
		result += "\t<number>" + client->Number() + "</number>\n";
		result += "\t<amount>" + std::to_string(client->Amount()) + "</amount>\n";
		result += "</person>\n";

		std::ofstream file("clients.xml", std::ios::app);
		file << result;
		file.close();
	}

	void VisitCompany(Company* client) override 
	{
		std::string result = "<company>\n";
		result += "\t<title>" + client->Title() + "</title>\n";
		result += "\t<number>" + client->Number() + "</number>\n";
		result += "\t<license>" + client->License() + "</license>\n";
		result += "\t<amount>" + std::to_string(client->Amount()) + "</amount>\n";
		result += "</company>\n";

		std::ofstream file("clients.xml", std::ios::app);
		file << result;
		file.close();
	}
};

class JsonVisitor : public IVisitor
{
public:
	void VisitPerson(Person* client) override 
	{
		std::string result = "{\n";
		result += "\t\"name\": \"" + client->Name() + ",\n";
		result += "\t\"number\": \"" + client->Number() + ",\n";
		result += "\t\"amount\": \"" + std::to_string(client->Amount()) + ",\n";
		result += "}\n";

		std::ofstream file("clients.json", std::ios::app);
		file << result;
		file.close();
	}
	
	void VisitCompany(Company* client) override
	{
		std::string result = "{\n";
		result += "\t\"title\": \"" + client->Title() + ",\n";
		result += "\t\"number\": \"" + client->Number() + ",\n";
		result += "\t\"license\": \"" + client->License() + ",\n";
		result += "\t\"amount\": \"" + std::to_string(client->Amount()) + ",\n";
		result += "}\n";

		std::ofstream file("clients.json", std::ios::app);
		file << result;
		file.close();
	}
};