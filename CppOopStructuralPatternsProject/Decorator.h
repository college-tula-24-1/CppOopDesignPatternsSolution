#pragma once
#include <iostream>

namespace DecoratorNamespace
{
	class Component
	{
	public:
		virtual ~Component() = default;
		virtual std::string Execute() = 0;
	};

	class ConcreteComponenet : public Component
	{
	public:
		std::string Execute() override
		{
			return "Execute Concrete Componenet";
		}
	};

	class Decorator : public Component
	{
	protected:
		Component* component;
	public:
		Decorator(Component* component)
			: component{ component }{ }
		
		std::string Execute() override
		{
			return this->component->Execute();
		}
	};

	class ConcreteDecoratorA : public Decorator
	{
	public:
		ConcreteDecoratorA(Component* component)
			: Decorator(component){ }

		std::string Execute() override
		{
			return " Concrete Decorator A with " + component->Execute();
		}
	};

	class ConcreteDecoratorB : public Decorator
	{
	public:
		ConcreteDecoratorB(Component* component)
			: Decorator(component) {
		}

		std::string Execute() override
		{
			return " Concrete Decorator B with " + component->Execute();
		}
	};

	class Client
	{
	public:
		void ClientCode(Component* component)
		{
			std::cout << "Result: " + component->Execute() << "\n";
		}
	};


	//

	class IMessage
	{
	protected:
		std::string from;
		std::string to;
		std::string text;
	public:
		std::string& From() { return from; }
		std::string& To() { return to; }
		std::string& Text() { return text; }

		virtual void Send() = 0;
		virtual ~IMessage() = default;
	};

	class MessangerMessage : public IMessage
	{
		std::string sticker;
	public:
		std::string& Sticker() { return sticker; }

		MessangerMessage()
			: sticker{ ":-)" }{ }

		void Send() override
		{
			std::cout << "Messanger send from: " << from
				<< "\nto: " << to
				<< "\ntext: " << text
				<< "\n" << sticker << "\n";
		}
	};

	class EmailMessage : public IMessage
	{
		std::string subject;
	public:
		std::string& Subject() { return subject; }

		EmailMessage()
			: subject{ "subject" } {}

		void Send() override
		{
			std::cout << "Email send from: " << from
				<< "\nto: " << to
				<< "\nsubject: " << subject
				<< "\ntext: " << text << "\n";
				
		}
	};

	class IMessageDecorator : public IMessage
	{
	protected:
		IMessage* message;
	public:
		IMessageDecorator(IMessage* message) 
			: message{ message }{}
	};

	class FileMessage : public IMessageDecorator
	{
		std::string file;
	public:
		FileMessage(IMessage* message, std::string file)
			: IMessageDecorator(message), file{ file }{ }

		void Send() override
		{
			message->Send();
			std::cout << "accept file: " << file << "\n";
		}
	};

	class ContactMessage : public IMessageDecorator
	{
		std::string contact;
	public:
		ContactMessage(IMessage* message, std::string contact)
			: IMessageDecorator(message), contact{ contact } {
		}

		void Send() override
		{
			message->Send();
			std::cout << "with contact info: " << contact << "\n";
		}
	};

	class MessageClient
	{
	public:
		void SendMessage(IMessage* message)
		{
			message->Send();
		}
	};
}
