#pragma once
#include <iostream>

class Context;

class State
{
protected:
	Context* context{};
public:
	virtual ~State() = default;
	void SetContext(Context* context) { this->context = context; }

	virtual void ExecuteOne() = 0;
	virtual void ExecuteTwo() = 0;
};

class Context
{
	State* state{};

public:
	Context(State* initState)
	{
		this->TransitionTo(initState);
	}

	void TransitionTo(State* state)
	{
		std::cout << "Context: Trasition to " << typeid(*state).name() << "\n";
		if (this->state)
			delete this->state;
		this->state = state;
		this->state->SetContext(this);
	}

	void HandlerOne() {	this->state->ExecuteOne(); }
	void HandlerTwo() { this->state->ExecuteTwo(); }

};

class ConcreteStateA : public State
{
public:
	void ExecuteOne() override;
	void ExecuteTwo() override
	{
		std::cout << "Concrete State A: Execute Two\n";
	}
};

class ConcreteStateB : public State
{
public:
	void ExecuteOne() override
	{
		std::cout << "Concrete State B: Execute One\n";
	}
	void ExecuteTwo() override
	{
		std::cout << "Concrete State B: Execute Two\n";
		std::cout << "Concrete State B: Transition Context\n";
		this->context->TransitionTo(new ConcreteStateA());
	}
};

void ConcreteStateA::ExecuteOne()
{
	std::cout << "Concrete State A: Execute One\n";
	std::cout << "Concrete State A: Transition Context\n";
	this->context->TransitionTo(new ConcreteStateB());
}

class StateClient
{
public:
	void ClientCode()
	{
		Context* context = new Context(new ConcreteStateA());
		context->HandlerOne();
		context->HandlerTwo();

		delete context;
	}
};

//

class Water;
class WaterState
{
protected:
	Water* water;
public:
	WaterState(Water* water = nullptr) : water{ water }{}
	void SetWater(Water* water) { this->water = water; }

	virtual void Heat() = 0;
	virtual void Frost() = 0;
};

class Water
{
	WaterState* state;
public:
	Water(WaterState* state) : state{ state }{}

	void Heating()
	{
		this->state->Heat();
	}

	void Frosting()
	{
		this->state->Frost();
	}

	WaterState*& State() 
	{ 
		if (this->state) delete this->state;

		return this->state; 
	}
};

class GasWaterState : public WaterState
{
public:
	GasWaterState(Water* water = nullptr) : WaterState(water) {}

	void Heat() override;
	void Frost() override;
};

class LiquidWaterState : public WaterState
{
public:
	LiquidWaterState(Water* water = nullptr) : WaterState(water) {}
	void Heat() override;
	void Frost() override;
};

class SolidWaterState : public WaterState
{
public:
	SolidWaterState(Water* water = nullptr) : WaterState(water) {}
	void Heat() override;
	void Frost() override;
};

void GasWaterState::Heat()
{
	std::cout << "Gas to hot gas\n";
}

void GasWaterState::Frost()
{
	std::cout << "Gas to liquid\n";
	this->water->State() = new LiquidWaterState(water);
}

void LiquidWaterState::Heat()
{
	std::cout << "Liquid to gas\n";
	this->water->State() = new GasWaterState(water);
}

void LiquidWaterState::Frost()
{
	std::cout << "Liquid to ice\n";
	this->water->State() = new SolidWaterState(water);
}

void SolidWaterState::Heat()
{
	std::cout << "Ice to liquid\n";
	this->water->State() = new LiquidWaterState(water);
}

void SolidWaterState::Frost()
{
	std::cout << "Ice to hard ice\n";
}

class WaterClient
{
public:
	void ClientCode()
	{
		WaterState* state = new LiquidWaterState();
		Water* water = new Water(state);
		state->SetWater(water);
		
		water->Heating();
		water->Heating();
		water->Heating();
		water->Frosting();
		water->Frosting();
		water->Frosting();
	}
	
};