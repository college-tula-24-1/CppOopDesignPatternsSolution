#pragma once
#include <iostream>
#include <string>

/*
RomanNumbert ::= {thousands} {hundres} {tens} {ones}

thousands, hundres, tens, ones ::= nine | fore | {five} {one} {one} {one}

nine ::= IX | XC | CM
fore ::= IV | XL | CD
five ::= V | L | D
one  ::= I | X | C | M

MCMXCVI 
1996

DCCCLXXXVIII
888
*/

class RNThousand;
class RNHundred;
class RNTen;
class RNOne;

class RNInterpreter
{
private:
	RNInterpreter* thousands;
	RNInterpreter* hundreds;
	RNInterpreter* tens;
	RNInterpreter* ones;
protected:
	virtual std::string One() { return ""; }
	virtual std::string Four() { return ""; }
	virtual std::string Five() { return ""; }
	virtual std::string Nine() { return ""; }
	virtual int Multiplier() { return 0; }
public:
	RNInterpreter();
	RNInterpreter(int){}

	int Interpret(std::string input);
	virtual void Interpret(std::string& input, int& result)
	{
		int position{};
		if ((input.substr(position, 2) == Nine()))
		{
			result += 9 * Multiplier();
			position += 2;
		}
		else if ((input.substr(position, 2) == Four()))
		{
			result += 4 * Multiplier();
			position += 2;
		}
		else
		{
			if (input.substr(position, 1) == Five())
			{
				result += 5 * Multiplier();
				position = 1;
			}
			else
				position = 0;
			for (int end{ position + 3 }; position < end; position++)
			{
				if (input.substr(position, 1) == One())
					result += 1 * Multiplier();
				else
					break;
			}
		}
		input = input.substr(position);
	}
};

class RNOne : public RNInterpreter
{
public:
	RNOne(int) : RNInterpreter(1){}
protected:
	virtual std::string One() { return "I"; }
	virtual std::string Four() { return "IV"; }
	virtual std::string Five() { return "V"; }
	virtual std::string Nine() { return "IX"; }
	virtual int Multiplier() { return 1; }
};

class RNTen : public RNInterpreter
{
public:
	RNTen(int) : RNInterpreter(10) {}
protected:
	virtual std::string One() { return "X"; }
	virtual std::string Four() { return "XL"; }
	virtual std::string Five() { return "L"; }
	virtual std::string Nine() { return "XC"; }
	virtual int Multiplier() { return 10; }
};

class RNHundred : public RNInterpreter
{
public:
	RNHundred(int) : RNInterpreter(100) {}
protected:
	virtual std::string One() { return "C"; }
	virtual std::string Four() { return "CD"; }
	virtual std::string Five() { return "D"; }
	virtual std::string Nine() { return "CM"; }
	virtual int Multiplier() { return 100; }
};

class RNThousand : public RNInterpreter
{
public:
	RNThousand(int) : RNInterpreter(1000) {}
protected:
	virtual std::string One() { return "M"; }
	virtual std::string Four() { return ""; }
	virtual std::string Five() { return ""; }
	virtual std::string Nine() { return ""; }
	virtual int Multiplier() { return 1000; }
};

RNInterpreter::RNInterpreter()
{
	this->thousands = new RNThousand(1);
	this->hundreds = new RNHundred(1);
	this->tens = new RNTen(1);
	this->ones = new RNOne(1);
}

inline int RNInterpreter::Interpret(std::string input)
{
	int result{};
	this->thousands->Interpret(input, result);
	this->hundreds->Interpret(input, result);
	this->tens->Interpret(input, result);
	this->ones->Interpret(input, result);

	if (!input.empty())
		return 0;
	return result;
}
