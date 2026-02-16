#pragma once
#include <iostream>
#include <stack>

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute() = 0;
	virtual bool CanExecute() { return true; }
};

///

class SimpleCommand : public ICommand
{
	std::string message;
public:
	SimpleCommand(std::string message)
		: message{ message }{ }
	void Execute() override
	{
		std::cout << "Print message: " << message << "\n";
	}
};

class Receiver
{
public:
	void DoSomethingIf(std::string message)
	{
		std::cout << "If TRUE: " << message << "\n";
	}

	void DoSomethingElse(std::string message)
	{
		std::cout << "If ELSE: " << message << "\n";
	}
};

class ComplexCommand : public ICommand
{
	Receiver* receiver;

	std::string messageIf;
	std::string messageElese;

public:
	ComplexCommand(Receiver* receiver, 
		std::string messageIf,
		std::string messageElese)
		: receiver{ receiver },
		messageIf{ messageIf},
		messageElese{ messageElese }{}
	
	void Execute() override
	{
		std::cout << "Complex command:\n";
		receiver->DoSomethingIf(messageIf);
		receiver->DoSomethingElse(messageElese);
	}
};

class Invoker
{
	ICommand* startCommand;
	ICommand* finishCommand;
public:
	~Invoker()
	{
		delete startCommand;
		delete finishCommand;
	}

	Invoker(ICommand* startCommand, ICommand* finishCommand)
		: startCommand{ startCommand },
		finishCommand{ finishCommand }{ }

	void DoInvokerStart()
	{
		if (startCommand && startCommand->CanExecute())
			startCommand->Execute();

		if (finishCommand && finishCommand->CanExecute())
			finishCommand->Execute();
	}
};

class CommandClient
{
public:
	void ClientCode()
	{
		SimpleCommand* simpleCommand = new SimpleCommand("Simple command");
		ComplexCommand* complexCommand = new ComplexCommand(new Receiver(), "First message", "Second message");
		Invoker* invoker = new Invoker(simpleCommand, complexCommand);
		invoker->DoInvokerStart();
	}
};


///
// Receiver
class Television
{
	bool isPower;
	int soundVolume;

	const int maxVolume{ 5 };
public:
	Television() : isPower{ false }, soundVolume{}{}

	void PowerOn()
	{
		std::cout << "Television power ON\n";
		isPower = true;
	}

	void PowerOff()
	{
		std::cout << "Television power OFF\n";
		isPower = false;
	}

	void VolumeAdd()
	{
		if(soundVolume < maxVolume)
			std::cout << "Television sound add. Volume: " << ++soundVolume << "\n";
	}

	void VolumeDel()
	{
		if(soundVolume > 0)
			std::cout << "Television sound del. Volume: " << --soundVolume << "\n";
	}

	bool IsPower() { return this->isPower; }

	void Info()
	{
		std::cout << "Power: " << ((isPower) ? "ON" : "OFF")
			<< "Sound: " << soundVolume << "\n";
	}
};

// interfaces
class IUndoCommand : public ICommand
{
public:
	virtual void Undo() = 0;
};

class ITvCommand : public IUndoCommand
{
protected:
	Television* tv;
public:
	ITvCommand(Television* tv) : tv{ tv } {};
};


class TvOnCommand : public ITvCommand
{
public:
	TvOnCommand(Television* tv) : ITvCommand(tv) {}
	void Execute() override { tv->PowerOn(); }
	bool CanExecute() override { return !tv->IsPower(); }
	void Undo() override { tv->PowerOff(); }
};

class TvOffCommand : public ITvCommand
{
public:
	TvOffCommand(Television* tv) : ITvCommand(tv) {}
	void Execute() override { tv->PowerOff(); }
	bool CanExecute() override { return tv->IsPower(); }
	void Undo() override { tv->PowerOn(); }
};

class TvSoundAddCommand : public ITvCommand
{
public:
	TvSoundAddCommand(Television* tv) : ITvCommand(tv) {}
	void Execute() override { tv->VolumeAdd(); }
	bool CanExecute() override { return tv->IsPower(); }
	void Undo() override { tv->VolumeDel(); }
};

class TvSoundDelCommand : public ITvCommand
{
public:
	TvSoundDelCommand(Television* tv) : ITvCommand(tv) {}
	void Execute() override { tv->VolumeDel(); }
	bool CanExecute() override { return tv->IsPower(); }
	void Undo() override { tv->VolumeAdd(); }
};

// Invoker
class Controller
{
	ITvCommand* powerOn;
	ITvCommand* powerOff;
	ITvCommand* soundUp;
	ITvCommand* soundDown;
public:
	Controller(ITvCommand* powerOn,
				ITvCommand* powerOff,
				ITvCommand* soundUp,
				ITvCommand* soundDown)
		: powerOn{ powerOn },
		powerOff{ powerOff },
		soundUp{ soundUp },
		soundDown{ soundDown } {}

	void ButtonPower()
	{
		if (powerOn->CanExecute())
			powerOn->Execute();
		else if (powerOff->CanExecute())
			powerOff->Execute();
	}
	void ButtonSoundPlus() 
	{ 
		if(soundUp->CanExecute())
			soundUp->Execute(); 
	}
	void ButtonSoundMinus() 
	{ 
		if(soundDown->CanExecute())
			soundDown->Execute(); 
	}
};

class MobileController
{
	ITvCommand* powerOn;
	ITvCommand* powerOff;
	ITvCommand* soundUp;
	ITvCommand* soundDown;

	std::stack<IUndoCommand*> history;
public:
	MobileController(ITvCommand* powerOn,
					ITvCommand* powerOff,
					ITvCommand* soundUp,
					ITvCommand* soundDown)
		: powerOn{ powerOn },
		powerOff{ powerOff },
		soundUp{ soundUp },
		soundDown{ soundDown } {}

	void MenuItemPowerOn()
	{
		if (powerOn->CanExecute())
		{
			powerOn->Execute();
			history.push(powerOn);
		}
	}

	void MenuItemPowerOff()
	{
		if (powerOff->CanExecute())
		{
			powerOff->Execute();
			history.push(powerOff);
		}
	}

	void MenuItemVolumePlus()
	{
		if (soundUp->CanExecute())
		{
			soundUp->Execute();
			history.push(soundUp);
		}
	}

	void MenuItemVolumeMinus()
	{
		if (soundDown->CanExecute())
		{
			soundDown->Execute();
			history.push(soundDown);
		}
	}

	void MenuItemUndo()
	{
		if (!history.empty())
		{
			history.top()->Undo();
			history.pop();
		}
	}
};
