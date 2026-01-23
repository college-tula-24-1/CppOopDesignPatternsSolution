#pragma once
#include <iostream>
#include <mutex>

std::mutex m;

class Singleton
{
	static Singleton* instance;
	Singleton(){}
public:
	static Singleton* GetInstance()
	{
		if (!instance)
			instance = new Singleton();
		return instance;
	}
};

Singleton* Singleton::instance = nullptr;

// Singleton
class OperationSystem
{
	static OperationSystem* _system;
	std::string title;
	OperationSystem(std::string title)
		: title{ title }{ }

public:
	std::string Title() const { return title; }

	static OperationSystem* GetSystem(std::string title)
	{
		std::lock_guard<std::mutex> lock(m);
		if (!_system)
			_system = new OperationSystem(title);
		return _system;
	}
};
OperationSystem* OperationSystem::_system = nullptr;

class Computer
{
	OperationSystem* system;
public:
	OperationSystem*& System() { return system; }

	void Lounch(std::string title)
	{
		system = OperationSystem::GetSystem(title);
	}
};
