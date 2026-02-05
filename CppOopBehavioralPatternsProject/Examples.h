#pragma once
#include <iostream>
#include "Vector.h"
#include "ForwardList.h"

#include "List.h"
using namespace ListNamespace;

class Examples
{
public:
    static void VectorIteratorExample()
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

    static void ForwardListIteratorExample()
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

    static void ListIteratorExample()
    {
        List<int>* list = new List<int>();

        list->PushFront(100);
        list->PushFront(200);
        list->PushFront(300);

        list->ConsoleShow();

        /*try
        {
            while (true)
            {
                std::cout << list->PopFront() << "\n";
                list->ConsoleShow();
            }
        }
        catch (std::exception* ex)
        {
            std::cout << ex->what() << "\n";
        }*/
    }
};

