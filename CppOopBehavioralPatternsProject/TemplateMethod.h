#pragma once
#include <iostream>

class AbstractClass
{
protected:
	// Base operators with implemetaion
	void BaseOperationOne()
	{
		std::cout << "Abstract Class. Base Operation One\n";
	}

	virtual void BaseOperationTwo()
	{
		std::cout << "Abstract Class. Base Operation Two\n";
	}

	// Required for implemetation operations
	virtual void RequiredOperationOne() = 0;
	virtual void RequiredOperationTwo() = 0;

	// Hooks. Maybe implementation
	virtual void HookOne(){}
	virtual void HookTwo() {}

public:
	void TemplateMethod()
	{
		this->BaseOperationOne();
		this->RequiredOperationOne();
		this->HookOne();

		
		this->RequiredOperationTwo();
		this->HookTwo();
		this->BaseOperationTwo();
	}
};

class ConcreteClassA : public AbstractClass
{
protected:
	void RequiredOperationOne() override
	{
		std::cout << "Concrete Class A. Required Operation One\n";
	}

	void RequiredOperationTwo() override
	{
		std::cout << "Concrete Class A. Required Operation Two\n";
	}
};

class ConcreteClassB : public AbstractClass
{
protected:
	void BaseOperationTwo() override
	{
		std::cout << "Concrete Class A. Base Operation Two\n";
	}

	void RequiredOperationOne() override
	{
		std::cout << "Concrete Class B. Required Operation One\n";
	}

	void RequiredOperationTwo() override
	{
		std::cout << "Concrete Class B. Required Operation Two\n";
	}

	void HookOne() override
	{
		std::cout << "Concrete Class B. Hook One\n";
	}

	void HookTwo() override
	{
		std::cout << "Concrete Class B. Hook Two\n";
	}
};

class TemplateMethodClient
{
public:
	void ClientCode()
	{
		AbstractClass* templateClass = new ConcreteClassA();
		templateClass->TemplateMethod();
		std::cout << "\n";
		delete templateClass;

		templateClass = new ConcreteClassB();
		templateClass->TemplateMethod();
		std::cout << "\n";
		delete templateClass;
	}
};

