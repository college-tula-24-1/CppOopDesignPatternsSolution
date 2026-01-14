#include <iostream>

// Vending
class IVending
{
public:
	virtual void Payment() = 0;
	virtual void Select() = 0;
	virtual void Receipt() = 0;
};

class BeverageVending : public IVending
{
	void Payment() override
	{
		std::cout << "Beverage Vending Payment\n";
	}

	void Select() override
	{
		std::cout << "Beverage Select\n";
	}

	void Receipt() override
	{
		std::cout << "Beverage Vending Receipt\n";
	}
};

class CigaretteVending : public IVending
{
	void Payment() override
	{
		std::cout << "Cigarette Vending Payment\n";
	}

	void Select() override
	{
		std::cout << "Cigarette Select\n";
	}

	void Receipt() override
	{
		std::cout << "Cigarette Vending Receipt\n";
	}
};

class UniversalVending : public IVending
{
	IVending* vending;
public:
	UniversalVending() : vending{ new BeverageVending() }{}

	~UniversalVending() { delete vending; }

	void Payment() override
	{
		vending->Payment();
	}

	void Select() override
	{
		vending->Select();
	}

	void Receipt() override
	{
		vending->Receipt();
	}

	void ToBeverage()
	{
		delete vending;
		vending = new BeverageVending();
	}

	void ToCigarette()
	{
		delete vending;
		vending = new CigaretteVending();
	}
};

