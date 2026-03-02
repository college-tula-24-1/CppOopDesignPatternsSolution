#pragma once
#include <iostream>
#include <vector>
#include <string>

typedef std::pair<std::string, std::string> Property;

class IStrategy
{
public:
	virtual ~IStrategy() = default;
	virtual std::string DoAlgorithm(std::string data) = 0;
};

class Context
{
	std::unique_ptr<IStrategy> strategy;
public:
	Context(std::unique_ptr<IStrategy>&& strategy)
		: strategy{ std::move(strategy) }{ }

	void SetStrategy(std::unique_ptr<IStrategy>&& strategy)
	{
		this->strategy = std::move(strategy);
	}

	void DoSomeBisnessLogic()
	{
		if (this->strategy)
		{
			std::cout << "Context: Execute strategy: "
				<< strategy->DoAlgorithm("aBcDe") << "\n";
		}
		else
			std::cout << "Context: Strategy is not settting\n";
	}
};

class ConcreteStrategyA : public IStrategy
{
public:
	std::string DoAlgorithm(std::string data) override
	{
		for (int i{}; i < data.length(); i++)
			if (data[i] > 64 && data[i] < 91)
				data[i] += 32;
		return data;
	}
};

class ConcreteStrategyB : public IStrategy
{
public:
	std::string DoAlgorithm(std::string data) override
	{
		for (int i{}; i < data.length(); i++)
			if (data[i] > 96 && data[i] < 123)
				data[i] -= 32;
		return data;
	}
};

class StrategyClient
{
public:
	void ClientCode()
	{
		Context* context = new Context(std::make_unique<ConcreteStrategyA>());
		context->DoSomeBisnessLogic();
		context->SetStrategy(std::make_unique<ConcreteStrategyB>());
		context->DoSomeBisnessLogic();
	}
};

///

class Object
{
	std::vector<Property> properties;
public:
	void AddProperty(Property property)
	{
		properties.push_back(property);
	}
	void AddProperty(std::string key, std::string value)
	{
		this->AddProperty(std::make_pair(key, value));
	}

	void RemoveProperty(std::string key)
	{
		auto it = std::ranges::find_if(properties, [key](auto property) 
			{
				return property.first == key;
			});
		properties.erase(it);
	}

	void ChangeProperty(std::string key, std::string value)
	{
		auto it = std::ranges::find_if(properties, [key](auto property)
			{
				return property.first == key;
			});

		if (it != std::ranges::end(properties))
			(*it).second = value;
		else
			this->AddProperty(key, value);
	}

	int Size() { return properties.size(); }

	Property At(int index)
	{
		return properties[index];
	}
};

class ISerializator
{
public:
	virtual std::string Serialize(Object* object) = 0;
	virtual Object* Deserialize(std::string text) = 0;
};