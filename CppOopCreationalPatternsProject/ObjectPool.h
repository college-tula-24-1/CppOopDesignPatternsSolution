#pragma once
#include <vector>

class Object
{
	static int globalId;
	int id;
public:
	Object() : id{ ++globalId } {}
	int operator()() { return id; }
};
int Object::globalId = 0;


class ObjectPool
{
	struct ObjectBox
	{
		Object* instance{};
		bool isUse{};
	};

	std::vector<ObjectBox> pool;
public:
	Object* CreateObject()
	{
		for(size_t i{}; i < pool.size(); i++)
			if (!pool[i].isUse)
			{
				pool[i].isUse = true;
				return pool[i].instance;
			}

		ObjectBox box{ new Object, true };
		pool.push_back(box);

		return box.instance;
	}

	void DeleteObject(Object* object)
	{
		for(size_t i{}; i < pool.size(); i++)
			if (pool[i].instance == object)
			{
				pool[i].isUse = false;
				break;
			}
	}

	virtual ~ObjectPool()
	{
		for (size_t i{}; i < pool.size(); i++)
			delete pool[i].instance;
	}
};

