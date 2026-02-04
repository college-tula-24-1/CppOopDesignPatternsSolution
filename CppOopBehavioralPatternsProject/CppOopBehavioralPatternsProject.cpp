#include <iostream>
#include "Vector.h"
#include "ForwardList.h"

void VectorIteratorExample();

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

    auto node = list.Find(key);
    list.Insert(node, 100);
    list.Show();

    auto it = list.GetForwardIterator();
    while (!it->IsEnd())
    {
        std::cout << it->Current() << " ";
        it->Next();
    }

}

void VectorIteratorExample()
{
    Vector<int> vector;
    for (int i{}; i < 10; i++)
        vector.PushBack(rand() % 100);

    for (size_t i{}; i < vector.Size(); i++)
        std::cout << vector[i] << " ";
    std::cout << "\n";

    auto it = vector.GetReverceIterator();
    while (!it->IsEnd())
    {
        std::cout << it->Current() << " ";
        it->Next();
    }
    std::cout << "\n";
}
