#pragma once
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

