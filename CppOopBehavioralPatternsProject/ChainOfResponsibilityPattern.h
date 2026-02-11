#pragma once
#include <iostream>
#include <vector>

class IHandler
{
public:
	virtual IHandler* SetNext(IHandler* handler) = 0;
	virtual std::string Handle(std::string request) = 0;
};

class BaseHandler : public IHandler
{
protected:
	IHandler* nextHandler;

public:
	BaseHandler(IHandler* nextHandler = nullptr) 
		: nextHandler{ nextHandler }{}

	IHandler* SetNext(IHandler* handler) override
	{
		this->nextHandler = handler;
		return handler;
		// $chain->SetNext(handler1)->SetNext(handler2)...
	}

	std::string Handle(std::string request) override
	{
		if (this->nextHandler)
		{
			return this->nextHandler->Handle(request);
		}

		return "";
	}
};

class ConcreteHandlerA : public BaseHandler
{
public:
	std::string Handle(std::string request) override
	{
		if (request == "RequestA")
			return "Handler A, handled request " + request + "\n";
		else
			return BaseHandler::Handle(request);
	}
};

class ConcreteHandlerB : public BaseHandler
{
public:
	std::string Handle(std::string request) override
	{
		if (request == "RequestB")
			return "Handler B, handled request " + request + "\n";
		else
			return BaseHandler::Handle(request);
	}
};

class ConcreteHandlerC : public BaseHandler
{
public:
	std::string Handle(std::string request) override
	{
		if (request == "RequestC")
			return "Handler C, handled request " + request + "\n";
		else
			return BaseHandler::Handle(request);
	}
};

class ChainClient
{
public:
	void ClientCode(IHandler* chain)
	{
		std::vector<std::string> requestes{ "RequestA", "RequestB", "RequestC", "RequestD"};
		for (std::string& request : requestes)
		{
			std::cout << "Request: " + request << "\n";
			std::string result = chain->Handle(request);
			if (!result.empty())
				std::cout << " " << result;
			else
				std::cout << " " << request << " not handleded\n";
		}
	}
};