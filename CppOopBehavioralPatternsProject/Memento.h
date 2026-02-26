#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <string>

class Memento
{
public:
	virtual ~Memento() = default;
	virtual std::string GetName() const = 0;
	virtual std::string GetDate() const = 0;

	virtual std::string GetState() const = 0;
};

class ConcreteMemento : public Memento
{
	std::string state;
	std::string date;

public:
	ConcreteMemento(std::string state) : state{ state }
	{
		std::time_t now = std::time(nullptr);
		char date_c[26];
		ctime_s(date_c, sizeof(date_c), &now);

		this->date = std::string(date_c);
	}

	std::string GetDate() const override { return this->date; }
	std::string GetName() const override
	{
		return this->date + " (" + this->state.substr(0, 10) + "...)";
	}

	std::string GetState() const override { return this->state; }
};

class Originator
{
	std::string state;

	std::string GenerateRandomState(int length = 20)
	{
		const char alphaNumbers[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		int alphaNumbersLength = sizeof(alphaNumbers) - 1;

		std::string randomState = "";
		for (int i{}; i < length; i++)
			randomState += alphaNumbers[std::rand() % alphaNumbersLength];

		return randomState;
	}

public:
	Originator(std::string state) : state{ state }
	{
		std::cout << "Originator init. Base state: " << this->state << "\n";
	}

	void DoSomething()
	{
		this->state = GenerateRandomState();
		std::cout << "Originator make new state: " << this->state << "\n";
	}

	Memento* CreateMemento()
	{
		return new ConcreteMemento(this->state);
	}

	void RestoreState(Memento* memento)
	{
		this->state = memento->GetState();
		std::cout << "Originator restore state: " << this->state << "\n";
		delete memento;
	}
};

class Caretaker
{
	std::vector<Memento*> history;
	Originator* originator;
public:
	Caretaker(Originator* originator) : originator{ originator }{}
	~Caretaker()
	{
		for (auto memento : this->history)
			delete memento;
		history.clear();
	}

	void Backup()
	{
		std::cout << "\nCaretaker make backup for Originator\n";
		this->history.push_back(this->originator->CreateMemento());
	}

	void Undo()
	{
		if (this->history.empty()) return;

		Memento* memento = this->history.back();
		this->history.pop_back();

		std::cout << "Caretaker undo state for Originator: " 
				  << memento->GetName() << "\n";
		this->originator->RestoreState(memento);
	}

	void History()
	{
		std::cout << "\n------ Caretaker history -------\n";
		for (auto memento : this->history)
			std::cout << memento->GetName() << "\n";
		std::cout << "--------------------------------\n";
	}
};

class MementoClient
{
public:
	void ClientCode()
	{
		Originator* originator = new Originator("First state for Originator");

		Caretaker* caretaker = new Caretaker(originator);
		caretaker->Backup();

		originator->DoSomething();
		caretaker->Backup();

		originator->DoSomething();
		caretaker->Backup();

		originator->DoSomething();
		caretaker->Backup();

		caretaker->History();

		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
	}
};


////
// Memento
class PlayerState
{
	int level;
	int points;
public:
	PlayerState(int level, int points)
		: level{ level }, points{ points }{ }

	int Level() const { return this->level; }
	int Points() const { return this->points; }
};

// Service
class Game
{
public:
	int Play()
	{
		return 2 + rand() % 6;
	}
};

// Originator
class Player
{
	int level;
	int points;

	Game* game;
public:
	Player() : points{}, level{ 1 }, game{ new Game() } {}

	void Play()
	{
		this->points += game->Play();
		this->level += this->points / 10;
		this->points = this->points % 10;
	}

	std::string State()
	{
		return "Level: " + std::to_string(this->level)
			+ ", Points: " + std::to_string(this->points);
	}

	PlayerState* Save()
	{
		return new PlayerState(this->level, this->points);
	}

	void Load(PlayerState* state)
	{
		this->level = state->Level();
		this->points = state->Points();
		delete state;
	}
};

// Caretaker
class PlayerHistory
{
	Player* player;
	std::vector<PlayerState*> history;
public:
	PlayerHistory(Player* player) : player{ player }{}

	void Save()
	{
		this->history.push_back(player->Save());
	}

	void Load()
	{
		if (history.empty()) return;

		player->Load(this->history.back());
		this->history.pop_back();
	}
};