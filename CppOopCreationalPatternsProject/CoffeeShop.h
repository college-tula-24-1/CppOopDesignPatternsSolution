#pragma once
#include <iostream>

enum class CoffeeType
{
    ESPRESSO,
    AMERICANO,
    CAFFE_LATTE,
    CAPPUCCINO
};

class Coffee
{

public:
    void grindCoffee()
    {
        // перемалываем кофе
    }
    void makeCoffee()
    {
        // делаем кофе
    }
    void pourIntoCup()
    {
        // наливаем в чашку
    }
};

class Americano : public Coffee {};
class Cappuccino : public Coffee {};
class CaffeLatte : public Coffee {};
class Espresso : public Coffee {};


class SimpleCoffeeFactory
{
public:
    Coffee* createCoffee(CoffeeType type) {
        Coffee* coffee = nullptr;

        switch (type) {
        case CoffeeType::AMERICANO:
            coffee = new Americano();
            break;
        case CoffeeType::ESPRESSO:
            coffee = new Espresso();
            break;
        case CoffeeType::CAPPUCCINO:
            coffee = new Cappuccino();
            break;
        case CoffeeType::CAFFE_LATTE:
            coffee = new CaffeLatte();
            break;
        }

        return coffee;
    }
};

class CoffeeShop {

    SimpleCoffeeFactory* coffeeFactory;
public:
    CoffeeShop(SimpleCoffeeFactory* coffeeFactory)
        : coffeeFactory{ coffeeFactory } {
    }

    Coffee* orderCoffee(CoffeeType type)
    {
        Coffee* coffee = coffeeFactory->createCoffee(type);
        coffee->grindCoffee();
        coffee->makeCoffee();
        coffee->pourIntoCup();

        std::cout << "Вот ваш кофе! Спасибо, приходите еще!\n";
        return coffee;
    }
};
