#pragma once
#include <iostream>
#include <vector>

namespace AbstractFactoryNamespace
{
	class Product
	{
	public:
		virtual ~Product() {}

		virtual std::string ProductOperation() = 0;
	};

	class ProductA : public Product
	{
	public:
		virtual std::string ProductAOperation() = 0;
	};

	class ProductB : public Product
	{
	public:
		virtual std::string ProductBOperation() = 0;
	};


	class ProductA1 : public ProductA
	{
	public:
		std::string ProductOperation() override
		{
			return "general operation with Product A1\n";
		}

		std::string ProductAOperation() override
		{
			return "special operation with Product A1\n";
		}
	};

	class ProductA2 : public ProductA
	{
	public:
		std::string ProductOperation() override
		{
			return "general operation with Product A2\n";
		}

		std::string ProductAOperation() override
		{
			return "special operation with Product A2\n";
		}
	};


	class ProductB1 : public ProductB
	{
	public:
		std::string ProductOperation() override
		{
			return "general operation with Product B1\n";
		}

		std::string ProductBOperation() override
		{
			return "special operation with Product B1\n";
		}
	};

	class ProductB2 : public ProductB
	{
	public:
		std::string ProductOperation() override
		{
			return "general operation with Product B2\n";
		}

		std::string ProductBOperation() override
		{
			return "special operation with Product B2\n";
		}
	};


	class AbstractFactory
	{
	public:
		virtual ~AbstractFactory() {}

		virtual ProductA* CreateProductA() = 0;
		virtual ProductB* CreateProductB() = 0;
	};

	class Factory1 : public AbstractFactory
	{
	public:
		ProductA* CreateProductA() override
		{
			return new ProductA1();
		}

		ProductB* CreateProductB() override
		{
			return new ProductB1();
		}
	};

	class Factory2 : public AbstractFactory
	{
	public:
		ProductA* CreateProductA() override
		{
			return new ProductA2();
		}

		ProductB* CreateProductB() override
		{
			return new ProductB2();
		}
	};

	class Client
	{
	public:
		static void ClientCode(AbstractFactory* factory)
		{
			ProductA* productA = factory->CreateProductA();
			ProductB* productB = factory->CreateProductB();

			std::cout << productA->ProductOperation();
			std::cout << productA->ProductAOperation();
			std::cout << productB->ProductOperation();
			std::cout << productB->ProductBOperation();
		}
	};



	class Unit
	{
	public:
		virtual ~Unit() {}
		virtual std::string Info() = 0;
	};

	class Infantry : public Unit
	{
	public:
		std::string Info() override
		{
			return "Infantry";
		}
	};

	class Archer : public Unit
	{
	public:
		std::string Info() override
		{
			return "Archer";
		}
	};

	class Cavalry : public Unit
	{
	public:
		std::string Info() override
		{
			return "Cavalry";
		}
	};

	class Original : public Unit
	{
	public:
		
	};

	
	class RomeInfantry : public Infantry
	{
	public:
		std::string Info() override
		{
			return "Rome " + Infantry::Info();
		}
	};

	class RomeArcher : public Archer
	{
	public:
		std::string Info() override
		{
			return "Rome " + Archer::Info();
		}
	};

	class RomeCavalry : public Cavalry
	{
	public:
		std::string Info() override
		{
			return "Rome " + Cavalry::Info();
		}
	};

	class RomeChariot : public Original
	{
	public:
		std::string Info() override
		{
			return "Rome Chariot";
		}
	};


	class CarthagenInfantry : public Infantry
	{
	public:
		std::string Info() override
		{
			return "Carthagen " + Infantry::Info();
		}
	};

	class CarthagenArcher : public Archer
	{
	public:
		std::string Info() override
		{
			return "Carthagen " + Archer::Info();
		}
	};

	class CarthagenCavalry : public Cavalry
	{
	public:
		std::string Info() override
		{
			return "Carthagen " + Cavalry::Info();
		}
	};

	class CarthagenElephant : public Original
	{
	public:
		std::string Info() override
		{
			return "Carthagen Elephant";
		}
	};


	class ArmyFactory
	{
	public:
		virtual ~ArmyFactory() {}

		virtual Infantry* CreateInfantry() = 0;
		virtual Archer* CreateArcher() = 0;
		virtual Cavalry* CreateCavalry() = 0;
		virtual Original* CreateOriginal() = 0;
	};

	class RomeArmyFactory : public ArmyFactory
	{
	public:
		Infantry* CreateInfantry() override
		{
			return new RomeInfantry();
		}

		Archer* CreateArcher() override
		{
			return new RomeArcher();
		}

		Cavalry* CreateCavalry() override
		{
			return new RomeCavalry();
		}

		Original* CreateOriginal() override
		{
			return new RomeChariot();
		}
	};

	class CarthagenArmyFactory : public ArmyFactory
	{
	public:
		Infantry* CreateInfantry() override
		{
			return new CarthagenInfantry();
		}

		Archer* CreateArcher() override
		{
			return new CarthagenArcher();
		}

		Cavalry* CreateCavalry() override
		{
			return new CarthagenCavalry();
		}

		Original* CreateOriginal() override
		{
			return new CarthagenElephant();
		}
	};


	class Army
	{
		std::vector<Infantry*> infantries;
		std::vector<Archer*> archers;
		std::vector<Cavalry*> cavalries;
		std::vector<Original*> originals;

		ArmyFactory* armyFactory;
		size_t size;
	public:
		Army(ArmyFactory* armyFactory, size_t size)
			: armyFactory{ armyFactory }, size{ size }
		{
			for (int i{}; i < size; i++)
				infantries.push_back(armyFactory->CreateInfantry());
			for (int i{}; i < size; i++)
				archers.push_back(armyFactory->CreateArcher());
			for (int i{}; i < size; i++)
				cavalries.push_back(armyFactory->CreateCavalry());
			for (int i{}; i < size; i++)
				originals.push_back(armyFactory->CreateOriginal());
		}

		std::string Info()
		{
			std::string result = "";
			
			result += "Infantries:\n";
			for (auto item : infantries)
				result += "\t" + item->Info() + "\n";

			result += "Archers:\n";
			for (auto item : archers)
				result += "\t" + item->Info() + "\n";

			result += "Cavalries:\n";
			for (auto item : cavalries)
				result += "\t" + item->Info() + "\n";

			result += "Originals:\n";
			for (auto item : originals)
				result += "\t" + item->Info() + "\n";

			return result;
		}

		~Army()
		{
			for (auto item : infantries)
				delete item;
			for (auto item : archers)
				delete item;
			for (auto item : cavalries)
				delete item;
			for (auto item : originals)
				delete item;
		}
	};
}
