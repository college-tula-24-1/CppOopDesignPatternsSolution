#include <iostream>

#include "ForwardList.h"

int main()
{
    srand(time(nullptr));

    ForwardList<int> list;

    for (int i{}; i < 10; i++)
        list.Push(rand() % 100);

    list.Show();

    /*for (int i{}; i < 5; i++)
    {
        std::cout << list.Pop() << "\n";
        list.Show();
    }*/
    std::cout << "Input key of search: ";
    int key;
    std::cin >> key;

    /*auto node = list.Find(key);
    list.Insert(node, 100);
    list.Show();

    auto it = list.GetForwardIterator();
    while (!it->IsEnd())
    {
        std::cout << it->Current() << " ";
        it->Next();
    }*/

    auto it = list.FindValue(key);
    std::cout << it->Current() << "\n";

    /*list.Insert(it, 500);*/
    std::cout << list.Remove(it) << "\n";
    list.Show();
}


