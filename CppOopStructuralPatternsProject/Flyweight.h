#pragma once
#include <iostream>
#include <map>

class SharedState
{
	std::string name;
	std::string color;
	std::string texture;

public:
	SharedState(std::string name,
				std::string color,
				std::string texture)
		: name{ name }, color{ color }, texture{ texture }{ }

	std::string Name() { return name; }
	std::string Color() { return color; }
	std::string Texture() { return texture; }

	std::string ToString()
	{
		return "Name: " + name + ", Color: " + color + ", Texture: " + texture;
	}
};

class UniqueState
{
	std::string owner;
public:
	UniqueState(std::string owner) : owner{ owner }{}

	std::string ToString()
	{
		return "Owner: " + owner;
	}
};

class Flyweight
{
	SharedState* sharedState;
public:
	Flyweight(SharedState* sharedState)
		: sharedState{ new SharedState(*sharedState) } {}
	Flyweight(const Flyweight& other)
		: sharedState{ new SharedState(*other.sharedState) } {}
	~Flyweight() { delete sharedState; }

	SharedState* GetSharedState() const { return sharedState; }

	void Operation(UniqueState& uniqueState) const
	{
		std::cout << "Flyweight: Shared State: " << sharedState->ToString()
			<< ", Unique State: " << uniqueState.ToString() << "\n";
	}

};

class FlyweightFactory
{
	std::map<std::string, Flyweight> flyweights;

	std::string GetKey(SharedState& sharedState)
	{
		return sharedState.Name() + "_" +
			sharedState.Color() + "_" +
			sharedState.Texture();
	}
public:
	FlyweightFactory(std::initializer_list<SharedState> sharedStates)
	{
		for (auto state : sharedStates)
			this->flyweights.insert(std::make_pair(this->GetKey(state), Flyweight(&state)));
	}

	Flyweight GetFlyweight(SharedState& sharedState)
	{
		std::string key = this->GetKey(sharedState);
		if (!this->flyweights.contains(key))
		{
			flyweights.insert(std::make_pair(key, Flyweight(&sharedState)));
		}

		return flyweights.at(key);
	}

	void ListFlyweights()
	{
		for (auto fly : flyweights)
			std::cout << fly.second.GetSharedState()->ToString() << "\n";
	}
};


// 

class House
{
protected:
	int stages;
	std::string texture;
public:
	virtual void Build(double x, double y) = 0;
};

class PanelHouse : public House
{
public:
	PanelHouse()
	{
		stages = 9;
		texture = "texture_panel.jpg";
	}

	void Build(double x, double y) override
	{
		std::cout << "Panel House:\n"
			<< "\tStages: " << stages << "\n"
			<< "\tTexture: " << texture << "\n"
			<< "\t[" << x << "," << y << "]\n";
	}
};

class BrickHouse : public House
{
public:
	BrickHouse()
	{
		stages = 5;
		texture = "texture_brick.jpg";
	}

	void Build(double x, double y) override
	{
		std::cout << "Brick House:\n"
			<< "\tStages: " << stages << "\n"
			<< "\tTexture: " << texture << "\n"
			<< "\t[" << x << "," << y << "]\n";
	}
};

class HouseFactory
{
	std::map<std::string, House*> houses;
public:
	HouseFactory(std::initializer_list<std::pair<std::string, House*>> housesList)
	{
		for (auto house : housesList)
			houses.insert(std::make_pair(house.first, house.second));
	}

	House* GetHouse(std::string key)
	{
		if (houses.contains(key))
			return houses[key];
		else
			return nullptr;
	}
};

class FlyweightClient
{
public: 
	void ClientCode()
	{
		HouseFactory* factory = new HouseFactory(
			{{"panel", new PanelHouse()},
			{"brick", new BrickHouse()}});

		double x{ 10.5 };
		double y{ 21.0 };

		for (int i{}; i < 5; i++)
		{
			House* brickHouse = factory->GetHouse("brick");
			if (brickHouse)
				brickHouse->Build(x, y);
			x += 2.5;
			y += 0.5;
		}
	}
};