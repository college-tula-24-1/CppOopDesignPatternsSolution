#include <iostream>
#include <vector>

#include "Builder.h"
using namespace BuilderNamespace;


// 1 Проблема
// 2 Решение
// 3 Структура (диаграмма классов)
// 4 Шаблонный код
// 5 Практические примеры
// 6 Анализ паттерна 
//		(применимость, плюсы, минусы, шаги реализации, связи)



int main()
{
    Builder* builder = new Builder();
    Product* product1 = builder->AddName("Product 1")
                                ->AddPartA()
                                ->AddPartB()
                                ->AddPartD()
                                ->AddPartE()
                                ->GetProduct();
    
    product1->Info();
}


