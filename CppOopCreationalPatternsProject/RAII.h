#pragma once
#include <iostream>
#include <fstream>

// Smart Pointer
template <typename T>
class SmartPointer
{
	T* value;
public:
	SmartPointer(T value = nullptr) : value{ value } {}

	//

	~SmartPointer() { delete value; }
};


// Managed Resource
class ResourceManager
{
	std::ofstream* file;
public:
	ResourceManager(const std::string& fileName)
	{
		file = new std::ofstream(fileName);
		if (!file->is_open())
			throw std::runtime_error("Failed to open file");
	}

	~ResourceManager()
	{
		if (file->is_open())
			file->close();
	}

	void Write(std::string data)
	{
		*file << data;
	}
};
