#pragma once

#include "FactoryMethod.h"
using namespace FactoryMethod;

#include "AbstractFactory.h"
using namespace AbstractFactoryNamespace;

#include "Builder.h"
using namespace BuilderNamespace;



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
	static void FactoryMethodExamples()
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

    static void BuilderExamples()
    {
        /*Builder* builder = new Builder();
        Product* product1 = builder->AddName("Product 1")
                                    ->AddPartA()
                                    ->AddPartB()
                                    ->AddPartD()
                                    ->AddPartE()
                                    ->GetProduct();

        product1->Info();*/

        QueryBuilder* builder = new QueryBuilder();

        Query* query = builder->Table("employees")
            ->Select("id")
            ->Select("last_name", "Last name")
            ->Select("first_name", "First name")
            ->Where("salary > 100000")
            ->Where("YEAR(birthDate) > 2000", BoolOperation::AND)
            ->Where("city = 'Moscow'", BoolOperation::OR)
            ->OrderBy("last_name")
            ->OrderBy("salary", false)
            ->GetQuery();

        std::cout << query->QueryString();
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

