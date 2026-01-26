

#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

namespace BridgeNamespace
{
	class Implementation
	{
	public:
		virtual ~Implementation() {}
		virtual std::string ImplementationOperation() = 0;
	};

	class Abstraction
	{
	protected:
		Implementation* implementor;
	public:
		Abstraction(Implementation* implementor)
			: implementor{ implementor } {
		}
		virtual ~Abstraction() {}

		virtual std::string AbstractOperation()
		{
			return "Abstraction. Base operation with " +
				this->implementor->ImplementationOperation();
		}
	};

	class ConcreteImplementationA : public Implementation
	{
	public:
		std::string ImplementationOperation() override
		{
			return "Implementation A";
		}
	};

	class ConcreteImplementationB : public Implementation
	{
	public:
		std::string ImplementationOperation() override
		{
			return "Implementation B";
		}
	};

	class ExtendedAbstraction : public Abstraction
	{
	public:
		ExtendedAbstraction(Implementation* implementor)
			: Abstraction(implementor){ }

		std::string AbstractOperation() override
		{
			return "Extended Abstraction. Extended operation with " +
				this->implementor->ImplementationOperation();
		}
	};

	class Client
	{
	public:
		void ClientCode(Abstraction* abstraction)
		{
			std::cout << abstraction->AbstractOperation() << "\n";
		}
	};

	//Implementation
	class Color
	{
	protected:
		std::string name;
	public:
		Color(std::string name) : name{ name }{}
		virtual std::string GetColor() = 0;
	};

	class Shape
	{
	protected:
		Color* color;
	public:
		virtual void Draw() = 0;
	};

	class Square : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Square draw at " << color->GetColor() << " color\n";
		}
	};

	class Circle : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Circle draw at " << color->GetColor() << " color\n";
		}
	};

	class Red : public Color
	{
	public:
		Red() : Color("Red"){}
		std::string GetColor()
		{
			return name;
		}
	};

	class Green : public Color
	{
	public:
		Green() : Color("Green") {}
		std::string GetColor()
		{
			return name;
		}
	};



	// Logger
	class LoggerImpl
	{
	public:
		virtual void Log(std::string message) = 0;
	};

	class Logger
	{
	protected:
		LoggerImpl* impl;

		std::string CreateMessage(std::string message)
		{
			auto now = std::chrono::system_clock::now();
			std::time_t t_c = std::chrono::system_clock::to_time_t(now);
			return std::ctime(&t_c) + std::string(": ") + message;
		}
	public:
		Logger(LoggerImpl* impl) : impl{ impl }{}

		virtual void Log(std::string message) = 0;
	};

	class SimpleThreadLogger : public Logger
	{
	public:
		SimpleThreadLogger(LoggerImpl* impl) : Logger(impl) {}
		void Log(std::string message) override
		{
			impl->Log(CreateMessage(message));
		}
	};

	//class ParallelThreadLogger : public Logger
	//{
	//	
	//public:
	//	ParallelThreadLogger(LoggerImpl* impl) : Logger(impl) {}
	//	void threadLog(std::string& message)
	//	{
	//		impl->Log(CreateMessage(message));
	//	}

	//	void Log(std::string message) override
	//	{
	//		std::jthread th(threadLog, message);
	//		//th.join();
	//	}
	//};

	class ConsoleLogger : public LoggerImpl
	{
	public:
		void Log(std::string message) override
		{
			std::cout << message << "\n";
		}
	};

	class FileLogger : public LoggerImpl
	{
		std::string fileName;
		std::ofstream file;
	public:
		FileLogger(std::string fileName) : fileName{ fileName }
		{
			file.open(fileName);
		}

		~FileLogger()
		{
			file.close();
		}

		void Log(std::string message) override
		{
			file << message << "\n";
		}
	};

	class System
	{
		Logger* logger{};
	public:
		System(Logger* logger) : logger{ logger }{}

		void Work()
		{
			for (int i{}; i < 5; i++)
			{
				int ms = 1000 + rand() % 3000;
				std::chrono::duration<int, std::milli> d(ms);
				std::this_thread::sleep_for(d);

				logger->Log(std::to_string(i) + " message");
			}
		}
	};
}

