#include <iostream>

#include "Adapter.h"
using namespace AdapterNamespace;

// 1 Проблема
// 2 Решение
// 3 Структура (диаграмма классов)
// 4 Шаблонный код
// 5 Практические примеры
// 6 Анализ паттерна 
//		(применимость, плюсы, минусы, шаги реализации, связи)

int main()
{
    Client* client = new Client();
    client->ClientCode(new ConcreteClassA());
    client->ClientCode(new ConcreteClassB());

    client->ClientCode(new ServiceAdapter(new Service(), 500));
}
