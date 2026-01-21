#pragma once
#include <iostream>
#include <map>

namespace PrototypeNamespace
{
	class Prototype
	{
	public:
		virtual ~Prototype() {}
		virtual Prototype* Clone() = 0;
	};

	class ValuePrototype : public Prototype
	{
		int value;
	public:
		Prototype* Clone() override
		{
			return new ValuePrototype(*this);
		}
	};

	class ReferencesPrototype : public Prototype
	{
		int* refernce{};
		int size{};
	public:
		ReferencesPrototype(int size)
		{
			this->refernce = new int[size];
			this->size = size;
		}

		Prototype* Clone() override
		{
			ReferencesPrototype* copy = new ReferencesPrototype(this->size);
			for (int i{}; i < this->size; i++)
				copy->refernce[i] = this->refernce[i];
			return copy;
		}
	};



	enum class UnitType
	{
		Inafantry,
		Archer,
		Cavalry
	};

	class Unit : public Prototype
	{
	protected:
		std::string name;
	public:
		Unit(std::string name = "") : name{name} {}
		virtual ~Unit() {}
		std::string& Name() { return name; }

		virtual std::string ToString()
		{
			return "Unit: " + name;
		}
	};

	class Factory
	{
	public:
		virtual Unit* Create() = 0;
	};

	class Infantry : public Unit
	{
	public:
		Infantry() : Unit("Infantry"){}
		Prototype* Clone() override
		{
			return new Infantry(*this);
		}
	};

	class InfantryFactory : public Factory
	{
	public:
		Unit* Create() override
		{
			return new Infantry();
		}
	};


	class Archer : public Unit
	{
	public:
		Archer() : Unit("Archer") {}
		Prototype* Clone() override
		{
			return new Archer(*this);
		}
	};

	class ArcherFactory : public Factory
	{
	public:
		Unit* Create() override
		{
			return new Archer();
		}
	};

	class Cavalry : public Unit
	{
	public:
		Cavalry() : Unit("Cavalry") {}
		Prototype* Clone() override
		{
			return new Cavalry(*this);
		}
	};

	class CavalryFactory : public Factory
	{
	public:
		Unit* Create() override
		{
			return new Cavalry();
		}
	};

	class ColneStores
	{
		std::map<UnitType, Prototype*> clones;
	public:
		Prototype* GetClone(UnitType type)
		{
			if (clones.contains(type))
				return clones[type]->Clone();

			Factory* factory{};
			
			switch (type)
			{
			case UnitType::Inafantry:
				factory = new InfantryFactory();
				break;
			case UnitType::Archer:
				factory = new ArcherFactory();
				break;
			case UnitType::Cavalry:
				factory = new CavalryFactory();
				break;
			default:
				break;
			}

			if (!factory) return nullptr;

			auto unit = (Prototype*)factory->Create();
			clones.insert(std::pair(type, unit));
			delete factory;

			return unit->Clone();
		}
	};
}

