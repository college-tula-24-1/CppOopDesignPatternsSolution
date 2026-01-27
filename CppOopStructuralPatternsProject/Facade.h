#pragma once
#include <iostream>

namespace FacadeNamespace
{
	class SubsystemA
	{
	public:
		std::string Operation1()
		{
			return "Subsystem A: Ready!";
		}
		//
		std::string OperationN()
		{
			return "Subsystem A: Go!";
		}
	};

	class SubsystemB
	{
	public:
		std::string Operation1()
		{
			return "Subsystem B: Ready!";
		}
		//
		std::string OperationM()
		{
			return "Subsystem B: Fire!";
		}
	};

	class Facade
	{
	protected:
		SubsystemA* subsystemA{};
		SubsystemB* subsystemB{};
	public:
		Facade(SubsystemA* subsystemA = nullptr,
			SubsystemB* subsystemB = nullptr)
		{
			this->subsystemA = subsystemA ? subsystemA : new SubsystemA();
			this->subsystemB = subsystemB ? subsystemB : new SubsystemB();
		}
		~Facade()
		{
			delete subsystemA;
			delete subsystemB;
		}

		std::string Operation()
		{
			std::string result = "Facade init subsystems:\n";
			result += subsystemA->Operation1() + "\n";
			result += subsystemB->Operation1() + "\n";

			result += "Facade activate subsystems:\n";
			result += subsystemA->OperationN() + "\n";
			result += subsystemB->OperationM() + "\n";

			return result;
		}
	};

	class FacadeClient
	{
	public:
		void ClientCode(Facade* facade)
		{
			std::cout << facade->Operation() << "\n";
		}
	};


	//


	class TextEditor
	{
	public:
		void CreateCode()
		{
			std::cout << "Writing Code\n";
		}

		void Save()
		{
			std::cout << "Saving Code To File\n";
		}
	};

	class Compiller
	{
	public:
		void Compile()
		{
			std::cout << "Compillin Application\n";
		}
	};

	class RuntimeEnvironment
	{
	public:
		void Execute()
		{
			std::cout << "Execute Application\n";
		}

		void Finish()
		{
			std::cout << "Finished Application\n";
		}
	};

	class Ide // Facade
	{
		TextEditor* editor;
		Compiller* compiller;
		RuntimeEnvironment* runtime;
	public:
		Ide(TextEditor* editor, 
			Compiller* compiller, 
			RuntimeEnvironment* runtime)
			: editor{ editor },
			compiller{ compiller },
			runtime{ runtime }{ }

		void Start()
		{
			editor->CreateCode();
			editor->Save();
			compiller->Compile();
			runtime->Execute();
		}

		void Stop()
		{
			runtime->Finish();
		}
	};

	class Programmer
	{
	public:
		void CreateApplication(Ide* ide)
		{
			ide->Start();
			ide->Stop();
		}
	};
}


