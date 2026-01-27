#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Flyweight.h"


// 1 Проблема
// 2 Решение
// 3 Структура (диаграмма классов)
// 4 Шаблонный код
// 5 Практические примеры
// 6 Анализ паттерна 
//		(применимость, плюсы, минусы, шаги реализации, связи)

int main()
{
    FlyweightClient* client = new FlyweightClient();
    client->ClientCode();
}
