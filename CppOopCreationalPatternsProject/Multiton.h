#pragma once
#include <iostream>
#include <string>
#include <map>
#include <mutex>

std::mutex mm;

enum class MultitonType
{
	ZERO,
	ONE,
	TWO
};

class Multiton
{
	static std::map<MultitonType, Multiton*> instances;
	int type;
	Multiton(int type) : type{ type } {}
public:
	static Multiton* GetInstance(MultitonType type)
	{
		std::lock_guard<std::mutex> lock(mm);
		if (!instances.contains(type))
			instances.insert(std::make_pair(type, new Multiton((int)type)));
		
		return instances.at(type);
	}
	
	std::string ToString()
	{
		return "Instance type: " + std::to_string(type);
	}
};

std::map<MultitonType, Multiton*> Multiton::instances;