#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>


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

	enum class BoolOperation
	{
		EMPTY,
		AND,
		OR,
		NOT
	};

	class Query
	{
		std::pair<std::string, std::string> tableName;
		std::vector<std::pair<std::string, std::string>> fieldsSelect;
		std::vector<std::pair<std::string, BoolOperation>> whereExpressions;
		std::vector<std::pair<std::string, bool>> fieldsOrder;
		
		std::string queryString{};
	public:
		/*std::pair<std::string, std::string>& TableName() { return tableName; }
		std::map<std::string, std::string>& FieldsSelect() { return fieldsSelect; }
		std::map<std::string, BoolOperation>& WhereExpressions() { return whereExpressions; }
		std::map<std::string, bool>& FieldsOrder() { return fieldsOrder; }*/

		friend class QueryBuilder;

		std::string QueryString() { return queryString; }
	};


	class QueryBuilder
	{
		Query* query{};
	public:
		QueryBuilder() : query{ new Query() } {}

		QueryBuilder* Reset(std::string tableName = "", std::string tableAlias = "")
		{
			delete query;
			query = new Query();
			if (tableName != "")
				this->Table(tableName, tableAlias);
			
			return this;
		}

		QueryBuilder* Table(std::string tableName, std::string tableAlias = "")
		{
			query->tableName = std::make_pair(tableName, tableAlias);
			return this;
		}

		QueryBuilder* Select(std::string fieldName, std::string fieldAlias = "")
		{
			query->fieldsSelect.push_back(std::make_pair(fieldName, fieldAlias));
			return this;
		}

		QueryBuilder* Where(std::string whereExpression,
							BoolOperation boolOperation = BoolOperation::EMPTY)
		{
			query->whereExpressions.push_back(std::make_pair(whereExpression, boolOperation));
			return this;
		}

		QueryBuilder* OrderBy(std::string fieldName, bool ascDirection = true)
		{
			query->fieldsOrder.push_back(std::make_pair(fieldName, ascDirection));
			return this;
		}

		Query* GetQuery()
		{
			std::string str = "SELECT ";

			// SELECT FIELDS
			if (!query->fieldsSelect.empty())
			{
				for (auto field : query->fieldsSelect)
				{
					str += field.first;
					if (field.second != "")
						str += " AS " + field.second;
					str += ", ";
				}
				str = str.substr(0, str.length() - 2);
			}
			else
				str += "*";
			str += "\n";

			// FROM TABLE NAME
			str += "\tFROM " + query->tableName.first;
			if (query->tableName.second != "")
				str += " AS " + query->tableName.second;
			str += "\n";

			// WHERE EXPRESSIONS
			if (!query->whereExpressions.empty())
			{
				str += "\tWHERE";
				for (auto expression : query->whereExpressions)
				{
					switch (expression.second)
					{
					case BoolOperation::AND:
						str += " AND "; break;
					case BoolOperation::OR:
						str += " OR "; break;
					default:
						str += " ";
					}
					str += expression.first;
				}
				str += "\n";
			}

			// ORDER BY FIELDS
			if (!query->fieldsOrder.empty())
			{
				str += "\tORDER BY";
				for (auto field : query->fieldsOrder)
				{
					str += " " + field.first + " ";
					if (field.second)
						str += "ASC";
					else
						str += "DESC";
					str += ", ";
				}
				str = str.substr(0, str.length() - 2);
				str += "\n";
			}
			
			query->queryString = str;

			return query;
		}
	};

}
