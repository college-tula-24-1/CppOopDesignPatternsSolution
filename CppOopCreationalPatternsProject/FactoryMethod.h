#pragma once
#include <iostream>
#include <string>
#include <vector>


/*
	Factory Method
	Фабричный метод

	1 Унифицировать создание разнотипных объектов.
	
	2 Создать общий интерфейс - фабричный метод.
*/

namespace FactoryMethod
{
	class Product
	{
	public:
		virtual std::string Operation() = 0;
		virtual ~Product() {}
	};

	class ProductA : public Product
	{
	public:
		std::string Operation() override
		{
			return "Operation Product A";
		}
	};

	class ProductB : public Product
	{
	public:
		std::string Operation() override
		{
			return "Operation Product B";
		}
	};



	class Creator
	{
	public:
		virtual Product* FactoryMethod() = 0;
		virtual ~Creator() {}

		std::string CreatorOperation()
		{
			Product* product = this->FactoryMethod();
			std::string result = "Creator operations: " + product->Operation();
			delete product;
			return result;
		}
	};

	class CreatorA : public Creator
	{
	public:
		Product* FactoryMethod() override
		{
			return new ProductA();
		}
	};

	class CreatorB : public Creator
	{
	public:
		Product* FactoryMethod() override
		{
			return new ProductB();
		}
	};

	class Client
	{
	public:
		static void ClientCode(Creator* creator)
		{
			std::cout << "Client code work: " << creator->CreatorOperation() << "\n";
		}
	};



	class Unit
	{
	protected:
		int attack;
		int defence;
		std::string name;
	public:
		virtual ~Unit(){}

		Unit(std::string name = "", int attack = 0, int defence = 0)
			: name{ name }, attack{ attack }, defence{ defence }{}

		virtual std::string Info() = 0;

	};

	class UnitFactory
	{
	public:
		virtual ~UnitFactory() {}

		virtual Unit* Create() = 0;
	};

	// Infantry
	class Infantry : public Unit
	{
	public:
		Infantry() : Unit("Infantry", 4, 6){}

		std::string Info() override
		{
			return "Infantry | Attack: " + std::to_string(this->attack)
				+ ", Defence: " + std::to_string(this->defence);
		}
	};

	class InfantryFactory : public UnitFactory
	{
	public:
		Unit* Create() override
		{
			return new Infantry();
		}
	};


	//Archer
	class Archer : public Unit
	{
	public:
		Archer() : Unit("Archer", 8, 5) {}

		std::string Info() override
		{
			return "Archer | Attack: " + std::to_string(this->attack)
				+ ", Defence: " + std::to_string(this->defence);
		}
	};

	class ArcherFactory : public UnitFactory
	{
	public:
		Unit* Create() override
		{
			return new Archer();
		}
	};

	// Cavalry
	class Cavalry : public Unit
	{
	public:
		Cavalry() : Unit("Cavalry", 12, 7) {}

		std::string Info() override
		{
			return "Cavalry | Attack: " + std::to_string(this->attack)
				+ ", Defence: " + std::to_string(this->defence);
		}
	};

	class CavalryFactory : public UnitFactory
	{
	public:
		Unit* Create() override
		{
			return new Cavalry();
		}
	};


}




