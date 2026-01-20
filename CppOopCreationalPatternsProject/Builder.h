#pragma once
#include <iostream>
#include <vector>


namespace BuilderNamespace
{
	class Product
	{
		std::string name;
		std::vector<std::string> parts;
	public:
		Product(std::string name = "") : name{name} {}
		
		void SetName(std::string name)
		{
			this->name = name;
		}

		void AddPart(std::string part)
		{
			parts.push_back(part);
		}

		void Info()
		{
			std::cout << "Name: " << name << "\n";
			for (auto part : parts)
				std::cout << part << "\n";
		}
	};

	class Builder
	{
		Product* product;
	public:
		Builder() : product{ new Product() }{}

		void Reset()
		{
			delete product;
			product = new Product();
		}

		Builder* AddName(std::string name) { product->SetName(name); return this; };
		Builder* AddPartA() { product->AddPart("Part A"); return this; }
		Builder* AddPartB() { product->AddPart("Part B"); return this; }
		Builder* AddPartC() { product->AddPart("Part C"); return this; }
		Builder* AddPartD() { product->AddPart("Part D"); return this; }
		Builder* AddPartE() { product->AddPart("Part E"); return this; }

		Product* GetProduct() { return product; }

		~Builder()
		{
			delete product;
		}
	};
}
