#pragma once

#include "FactoryMethod.h"
using namespace FactoryMethod;

#include "AbstractFactory.h"
using namespace AbstractFactoryNamespace;

FactoryMethod::Unit* FactoryBad(int id)
{
    FactoryMethod::Unit* unit;
    switch (id)
    {
    case 1: return new FactoryMethod::Infantry();
    case 2: return new FactoryMethod::Archer();
    case 3: return new FactoryMethod::Cavalry();
    default: return nullptr;
    }
}

class FactoryGood
{
    std::vector<UnitFactory*> unitFactories;
    std::vector<Unit*> army;
public:
    std::vector<UnitFactory*>& UnitFactories() { return unitFactories; }

    void CreateArmy(int count);
    void InfoArmy();
};

class Examples
{
public:
	void FactoryMethodExamples()
	{
        std::cout << "App: Launched Creator A:\n";
        FactoryMethod::Client::ClientCode(new FactoryMethod::CreatorA());

        std::cout << "App: Launched Creator B:\n";
        FactoryMethod::Client::ClientCode(new CreatorB());

        FactoryGood unitArmy;
        unitArmy.UnitFactories().push_back(new InfantryFactory());
        unitArmy.UnitFactories().push_back(new ArcherFactory());

        unitArmy.CreateArmy(10);
        unitArmy.InfoArmy();
        std::cout << "\n";

        unitArmy.UnitFactories().push_back(new CavalryFactory());
        unitArmy.CreateArmy(10);
        unitArmy.InfoArmy();
        std::cout << "\n";
	}

    static void AbstractFactoryExamples()
    {
        AbstractFactoryNamespace::Client::ClientCode(new Factory1());
        std::cout << "\n";
        AbstractFactoryNamespace::Client::ClientCode(new Factory2());

        Army* romeArmy = new Army(new RomeArmyFactory(), 5);
        Army* carthagenArmy = new Army(new CarthagenArmyFactory(), 5);

        std::cout << "Rome Army:\n" << romeArmy->Info() << "\n";
        std::cout << "Carthagen Army:\n" << carthagenArmy->Info() << "\n";
    }
};

void FactoryGood::CreateArmy(int count)
{
    if (this->unitFactories.size() == 0) return;

    army.clear();
    for (int i{}; i < count; i++)
    {
        int type = rand() % unitFactories.size();
        army.push_back(unitFactories[type]->Create());
    }
}

void FactoryGood::InfoArmy()
{
    for (auto unit : army)
    {
        std::cout << unit->Info() << "\n";
    }
}

