#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>


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
		std::vector<std::string> requestes{ "RequestA", "RequestB", "RequestC", "RequestD" };
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


//
enum class PayType
{
	Sberbank,
	TBank,
	WesternUnion
};

class PayRequest
{
	std::map<PayType, bool> payMap;
	int amount;
public:
	PayRequest(int amount = 0) : amount{ amount }
	{
		payMap[PayType::Sberbank] =
			payMap[PayType::TBank] =
			payMap[PayType::WesternUnion] = false;
	}

	void PayCheck(PayType type)
	{
		payMap[type] = !payMap[type];
	}

	bool IsPay(PayType type)
	{
		return payMap[type];
	}

	int Amount() { return this->amount; }
};

class PaymentHandler
{
protected:
	PaymentHandler* successor{ nullptr };

public:
	PaymentHandler*& Successor() { return this->successor; }

	void Push(PaymentHandler* successor)
	{
		if (this->successor)
			this->successor->Push(successor);
		else
			this->successor = successor;
	}

	void Insert(PaymentHandler* successor)
	{

	}

	void NextSuccessor(PayRequest* request)
	{
		if (this->successor)
			this->successor->PayHandle(request);
	}

	virtual void PayHandle(PayRequest* request) = 0;
};

class SberPaymentHandler : public PaymentHandler
{
public:
	void PayHandle(PayRequest* request) override
	{
		if (request->IsPay(PayType::Sberbank))
		{
			// payment with Sber API
			std::cout << "Sber transfer is Ok. Amount: "
				+ std::to_string(request->Amount()) + "\n";
		}
		else
		{
			std::cout << "Sber transfer is None\n";
			PaymentHandler::NextSuccessor(request);
		}
	}
};

class TBankPaymentHandler : public PaymentHandler
{
public:
	void PayHandle(PayRequest* request) override
	{
		if (request->IsPay(PayType::TBank))
		{
			// payment with Sber API
			std::cout << "T-Bank transfer is Ok. Amount: "
				+ std::to_string(request->Amount()) + "\n";
		}
		else
		{
			std::cout << "T-Bank transfer is None\n";
			PaymentHandler::NextSuccessor(request);
		}
	}
};

class WesternUnionPaymentHandler : public PaymentHandler
{
public:
	void PayHandle(PayRequest* request) override
	{
		if (request->IsPay(PayType::WesternUnion))
		{
			// payment with Sber API
			std::cout << "WesternUnion transfer is Ok. Amount: "
				+ std::to_string(request->Amount()) + "\n";
		}
		else
		{
			std::cout << "WesternUnion transfer is None\n";
			PaymentHandler::NextSuccessor(request);
		}
	}
};

//
enum class Roles
{
	All,
	Admin
};

class Page
{
	std::string url;
	Roles roles;
	std::string content;
public:
	Page(std::string url,
		 std::string content,
		 Roles roles = Roles::All)
		: url{ url }, 
		content{ content },
		roles{ roles } { }

	std::string Url() { return this->url; }
	Roles Roles() { return this->roles; }

	std::string& Content() { return this->content; }
};

class WebServer
{
	std::vector<Page*> pages;
public:
	WebServer()
	{
		pages.push_back(new Page("/", "Home Page"));
		pages.push_back(new Page("about", "About Company Page"));
		pages.push_back(new Page("gallery", "Work's Gallery"));
		pages.push_back(new Page("contacts", "Contacts Info"));

		pages.push_back(new Page("admin", "Dashboard Main", Roles::Admin));
		pages.push_back(new Page("admin/gallery", "Dashboard Gallery", Roles::Admin));
	}

	Page* GetPage(std::string url)
	{
		auto it = std::ranges::find_if(pages, [url](Page* page) {
			return page->Url() == url;
			});
		return *it;
	}
};

class Database
{
	std::map<std::string, std::string> admins;
public:
	Database()
	{
		admins.insert("bobby", "qwerty");
		admins.insert("sammy", "12345");
		admins.insert("jimmy", "jimmy");
	}

	bool IsLogin(std::string login)
	{
		return admins.contains(login);
	}

	bool IsAdmin(std::string login, std::string password)
	{
		return admins[login] == password;
	}
};

class WebRequest
{
	std::string url{};
	std::string login{};
	std::string password{};
public:
	WebRequest(std::string url,
		std::string login = "",
		std::string password = "")
		: url{ url }, login{ login }, password{ password } {}

	std::string Url() { return this->url; }
	std::string Login() { return this->login; }
	std::string Password() { return this->password; }
};


class FormHandler
{
protected:
	FormHandler* nextHandler;
public:
	virtual void Handle(WebRequest* request) = 0;
};

class IsPageHandler : public FormHandler
{
	// проверяем есть ли страница на веб сервере
	// если нет - то возвращаем 404
	// если есть и доступ All, то возвращаем страницу.
	// если есть и доступ Admin, то передат на проверку дальше
};

class IsLoginHandler : public FormHandler
{
	// проверка есть ли логин в БД
	// если нет возвращаем - not found
	// если да - отправляем на проверку пароля
};

class IsAdminHandler : public FormHandler
{
	// проверка на совпадение пароля
	// если нет возвращаем - incorrect passord
	// если да возвращаем страницу
};


