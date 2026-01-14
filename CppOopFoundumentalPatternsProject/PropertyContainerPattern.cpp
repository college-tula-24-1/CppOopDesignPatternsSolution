#include <iostream>
#include <map>
#include <vector>

class Movie
{
	static int globalId;

	int id;
	std::string title;

	std::map<std::string, std::string> properties;
public:
	Movie() : id{ ++globalId } {}

	int Id() const { return id; }
	std::string& Title() { return title; }

	void SetProperty(std::string propertyName, std::string propertyValue)
	{
		if (propertyName.empty()) return;
		if (properties.contains(propertyName))
			properties[propertyName] = propertyValue;
		else
			properties.insert(std::make_pair(propertyName, propertyValue));
	}

	std::string GetProperty(std::string propertyName)
	{
		if (propertyName.empty() || !properties.contains(propertyName))
			return nullptr;
		
		return properties[propertyName];
	}

	void DeleteProperty(std::string propertyName)
	{
		if (propertyName.empty() || !properties.contains(propertyName))
			return;

		properties.erase(propertyName);
	}

	std::vector<std::string> GetPropertyNames()
	{
		std::vector<std::string> propertyNames;
		
		for (auto it{ properties.begin() }; it != properties.end(); it++)
			propertyNames.push_back(it->first);

		return propertyNames;
	}
};

int Movie::globalId = 0;