#pragma once
#include <iostream>
#include <map>

/*
IExpression ::= NumberExpession | Constant | BinaryOperation
BynaryOperation ::= AddOperation | SubstracOperation | MultiplyOperation | DivideOperation
AddOperation ::= IExpression + IExpression
...
NumberExpession ::= [A-Za-z]+
Constant ::= [0-9.e-]+
*/
class Context;

class IExpression
{
public:
	virtual double Interpret(Context* context) = 0;
};

class Context
{
	std::map<std::string, double> variables;
public:
	double GetVariable(std::string name)
	{
		return variables[name];
	}

	void SetVariable(std::string name, double value)
	{
		variables[name] = value;
	}
};

class NumberExpression : public IExpression
{
	std::string name;
public:
	NumberExpression(std::string name) : name{ name }{}

	double Interpret(Context* context) override
	{
		return context->GetVariable(name);
	}
};

class AddOperation : public IExpression
{
	IExpression* left;
	IExpression* right;
public:
	AddOperation(IExpression* left, IExpression* right)
		: left{ left }, right{ right } {}

	double Interpret(Context* context) override
	{
		return left->Interpret(context) + right->Interpret(context);
	}
};

class MultOperation : public IExpression
{
	IExpression* left;
	IExpression* right;
public:
	MultOperation(IExpression* left, IExpression* right)
		: left{ left }, right{ right } {
	}

	double Interpret(Context* context) override
	{
		return left->Interpret(context) * right->Interpret(context);
	}
};