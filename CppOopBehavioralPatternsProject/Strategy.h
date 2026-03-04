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

	Property At(std::string key)
	{
		auto it = std::ranges::find_if(properties, [key](auto item)
			{
				return item.first == key;
			});
		if (it != std::ranges::end(properties))
			return *it;
		
		throw new std::exception("not found property");
	}
};

class ISerializer
{
public:
	virtual std::string Serialize(Object* object) = 0;
	virtual Object* Deserialize(std::string text) = 0;
};

class JsonSerializer : public ISerializer
{
public:
	std::string Serialize(Object* object) override
	{
		std::string json{ "{\n" };

		for (int i{}; i < object->Size(); i++)
		{
			json += "\t\"" + object->At(i).first + "\": \""
				+ object->At(i).second + "\",\n";
		}

		json += "}\n";
		return json;
	}

	Object* Deserialize(std::string text) override
	{
		int position{};
		int length{};
		Object* object = new Object();

		while (position < text.length())
		{
			position = text.find("\"", position) + 1;
			
			if (!position) break;

			length = text.find("\"", position) - position;
			std::string key = text.substr(position, length);
			position += length + 1;

			position = text.find("\"", position) + 1;
			length = text.find("\"", position) - position;
			std::string value = text.substr(position, length);
			position += length + 1;

			object->AddProperty(key, value);
		}

		return object;
	}
};

class XmlSerializer : public ISerializer
{
public:
	std::string Serialize(Object* object) override
	{
		std::string xml{ "<object>\n" };
		for (int i{}; i < object->Size(); i++)
		{
			xml += "\t<" + object->At(i).first + ">"
				+ object->At(i).second 
				+ "</" + object->At(i).first + ">\n";
		}
		xml += "</object>\n";

		return xml;
	}

	Object* Deserialize(std::string text) override
	{
		Object* object = new Object();
		int position{};
		int length{};

		while (position < text.size())
		{
			position = text.find("<", position) + 1;
			if (!position) break;
			length = text.find(">", position) - position;
			std::string key = text.substr(position, length);
			position += length + 1;
			if (key == "object")
				continue;
			if (key == "/object")
				break;

			length = text.find("</", position) - position;
			std::string value = text.substr(position, length);
			position = text.find(">", position) + 1;

			object->AddProperty(key, value);
		}

		return object;
	}
};

class UniversalSerializer : public ISerializer
{
	ISerializer* serializer;
public:
	UniversalSerializer(ISerializer* serializer)
		: serializer{ serializer }{ }
	void SetSerializer(ISerializer* serializer)
	{
		this->serializer = serializer;
	}

	std::string Serialize(Object* object) override
	{
		return serializer->Serialize(object);
	}

	Object* Deserialize(std::string text) override
	{
		return serializer->Deserialize(text);
	}
};