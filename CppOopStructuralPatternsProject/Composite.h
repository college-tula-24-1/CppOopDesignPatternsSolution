#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string>

namespace ComponenetNamespace
{
	class Componenet
	{
	protected:
		Componenet* parent;
	public:
		virtual ~Componenet() {}
		Componenet*& Parent() { return parent; }
		bool IsComposite() { return false; }

		virtual std::string Execute(int level) = 0;
	};

	class Leaf : public Componenet
	{
	public:
		std::string Execute(int level) override
		{
			std::string tabs = "";
			for (int i{}; i < level; i++)
				tabs += "\t";

			return tabs + "Leaf";
		}
	};

	class Composite : public Componenet
	{
	protected:
		std::vector<Componenet*> componenets;
	public:
		std::string Execute(int level) override
		{
			std::string result = "";
			std::string tabs = "";
			for (int i{}; i < level; i++)
				tabs += "\t";
			for (auto item : componenets)
				result += item->Execute(level + 1) + "\n";
			return tabs + "Branch (\n" + result + tabs + ")";
		}

		void Add(Componenet* componenet)
		{
			componenets.push_back(componenet);
			componenet->Parent() = this;
		}

		void Remove(Componenet* componenet)
		{
			auto it = std::ranges::find(componenets, componenet);
			componenets.erase(it);
			(*it)->Parent() = nullptr;
		}

		bool IsComposite() { return true; }
	};

	class Client
	{
	public:
		void ClientCode()
		{
			Componenet* folder1 = new Composite();
			((Composite*)folder1)->Add(new Leaf());
			((Composite*)folder1)->Add(new Leaf());

			Componenet* folder2 = new Composite();
			((Composite*)folder2)->Add(new Leaf());
			((Composite*)folder2)->Add(folder1);

			std::cout << folder2->Execute(0) << "\n";
		}
	};



	// Units Army
	class Unit
	{
	protected:
		int attack{};
		int defence{};
		std::string name;
	public:
		Unit(std::string name, int attack, int defence)
			: name{ name }, attack{ attack }, defence{ defence } {}
		
		virtual int Attack() const = 0;
		virtual int Defence() const = 0;
		virtual void Info(int level) = 0;
	};

	class Factory
	{
	public:
		virtual Unit* CreateUnit() = 0;
	};

	class Infantry : public Unit
	{
	public:
		Infantry() : Unit("Infantry", 6, 5) {}
		
		int Attack() const override { return this->attack; }
		int Defence() const override { return this->defence; }

		void Info(int level) override
		{
			std::string tabs = "";
			for (int i{}; i < level; i++)
				tabs += "\t";
			std::cout << tabs + name +
				" [" + std::to_string(Attack()) + "," +
				std::to_string(Defence()) + "]\n";
		}

	};

	class InfantryFactory : public Factory
	{
	public:
		Unit* CreateUnit() override { return new Infantry(); }
	};

	class Archer : public Unit
	{
	public:
		Archer() : Unit("Archer", 8, 4) {}

		int Attack() const override { return this->attack; }
		int Defence() const override { return this->defence; }

		void Info(int level) override
		{
			std::string tabs = "";
			for (int i{}; i < level; i++)
				tabs += "\t";
			std::cout << tabs + name +
				" [" + std::to_string(Attack()) + "," +
				std::to_string(Defence()) + "]\n";
		}
	};

	class ArcherFactory : public Factory
	{
	public:
		Unit* CreateUnit() override { return new Archer(); }
	};

	class Cavalry : public Unit
	{
	public:
		Cavalry() : Unit("Cavalry", 10, 7) {}

		int Attack() const override { return this->attack; }
		int Defence() const override { return this->defence; }

		void Info(int level) override
		{
			std::string tabs = "";
			for (int i{}; i < level; i++)
				tabs += "\t";
			std::cout << tabs + name +
				" [" + std::to_string(Attack()) + "," +
				std::to_string(Defence()) + "]\n";
		}
	};

	class CavalryFactory : public Factory
	{
	public:
		Unit* CreateUnit() override { return new Cavalry(); }
	};

	class MilitaryUnit : public Unit
	{
		std::vector<Unit*> units;
	public:
		MilitaryUnit(std::string name)
			: Unit(name, 0, 0){ }

		int Attack() const override 
		{ 
			int attackTotal{};
			for (auto unit : units)
				attackTotal += unit->Attack();
			return attackTotal;
		}

		int Defence() const override
		{
			int defenceTotal{};
			for (auto unit : units)
				defenceTotal += unit->Defence();
			return defenceTotal;
		}

		void Add(Unit* unit) { units.push_back(unit); }

		void Info(int level) override
		{
			std::string tabs = "";
			for (int i{}; i < level; i++)
				tabs += "\t";
			std::cout << tabs + name +
				" [" + std::to_string(Attack()) + "," +
				std::to_string(Defence()) + "]\n";
			for (auto unit : units)
				unit->Info(level + 1);
		}
	};

	class Army
	{
		Unit* army{};
	public:
		void CreateArmy()
		{
			int infantriesCount{ 10 + rand() % 20 };
			int archearsCount{ 10 + rand() % 20 };
			int cavalryCount{ 10 + rand() % 20 };

			Unit* infantryMilitaryUnit = new MilitaryUnit("Infantry Legion");
			Factory* factory = new InfantryFactory();

			for (int i{}; i < infantriesCount; i++)
				((MilitaryUnit*)infantryMilitaryUnit)->Add(factory->CreateUnit());

			delete factory;
			factory = new ArcherFactory();
			Unit* archersMilitaryUnit = new MilitaryUnit("Archer Legion");
			for (int i{}; i < archearsCount; i++)
				((MilitaryUnit*)archersMilitaryUnit)->Add(factory->CreateUnit());

			delete factory;
			factory = new CavalryFactory();
			Unit* cavalriesMilitaryUnit = new MilitaryUnit("Cavaleries Legion");
			for (int i{}; i < cavalryCount; i++)
				((MilitaryUnit*)cavalriesMilitaryUnit)->Add(factory->CreateUnit());

			army = new MilitaryUnit("Army");
			((MilitaryUnit*)army)->Add(infantryMilitaryUnit);
			((MilitaryUnit*)army)->Add(archersMilitaryUnit);
			((MilitaryUnit*)army)->Add(cavalriesMilitaryUnit);
		}

		void Info()
		{
			army->Info(0);
		}
	};
}


