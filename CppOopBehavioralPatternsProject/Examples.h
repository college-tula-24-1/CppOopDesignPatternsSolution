#pragma once
#include <iostream>
#include "Vector.h"
#include "ForwardList.h"

#include "List.h"
using namespace ListNamespace;

#include "ChainOfResponsibilityPattern.h"
#include "Command.h"
#include "Mediator.h"
#include "Memento.h"

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

        srand(time(nullptr));

        //ForwardList<int> list;

        //for (int i{}; i < 10; i++)
        //    list.Push(rand() % 100);

        //list.Show();

        ///*for (int i{}; i < 5; i++)
        //{
        //    std::cout << list.Pop() << "\n";
        //    list.Show();
        //}*/
        //std::cout << "Input key of search: ";
        //int key;
        //std::cin >> key;

        ///*auto node = list.Find(key);
        //list.Insert(node, 100);
        //list.Show();

        //auto it = list.GetForwardIterator();
        //while (!it->IsEnd())
        //{
        //    std::cout << it->Current() << " ";
        //    it->Next();
        //}*/

        //auto it = list.FindValue(key);
        //std::cout << it->Current() << "\n";

        ///*list.Insert(it, 500);*/
        //std::cout << list.Remove(it) << "\n";
        //list.Show();
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

    static void ChainOfResponsibilityExamples()
    {
        /*ConcreteHandlerA* handlerA = new ConcreteHandlerA();
    ConcreteHandlerB* handlerB = new ConcreteHandlerB();
    ConcreteHandlerC* handlerC = new ConcreteHandlerC();

    handlerA->SetNext(handlerB)->SetNext(handlerC);

    ChainClient* client = new ChainClient();
    client->ClientCode(handlerA);
    std::cout << "\n";*/

        PaymentHandler* payChain = new SberPaymentHandler();
        payChain->Push(new WesternUnionPaymentHandler());
        payChain->Push(new TBankPaymentHandler());

        PayRequest* request = new PayRequest(1000);
        payChain->PayHandle(request);
        std::cout << "\n";

        request->PayCheck(PayType::TBank);
        request->PayCheck(PayType::Sberbank);
        payChain->PayHandle(request);
        std::cout << "\n";
    }

    static void CommandExamples()
    {
        Television* tv = new Television();
        Controller* pult = new Controller(
            new TvOnCommand(tv),
            new TvOffCommand(tv),
            new TvSoundAddCommand(tv),
            new TvSoundDelCommand(tv));

        //pult->ButtonPower();
        //pult->ButtonPower();
        //pult->ButtonSoundPlus();
        //pult->ButtonSoundPlus();
        //pult->ButtonSoundPlus();
        //pult->ButtonSoundMinus();

        MobileController* app = new MobileController(
            new TvOnCommand(tv),
            new TvOffCommand(tv),
            new TvSoundAddCommand(tv),
            new TvSoundDelCommand(tv));

        app->MenuItemPowerOn();

        tv->Info();

        app->MenuItemVolumePlus();
        app->MenuItemVolumePlus();
        app->MenuItemVolumeMinus();
        app->MenuItemVolumePlus();
        app->MenuItemVolumePlus();
        app->MenuItemVolumeMinus();


        tv->Info();

        for (int i{}; i < 4; i++)
            app->MenuItemUndo();

        tv->Info();
    }

    static void MediatrExamples()
    {
        //ComponentA* cA = new ComponentA();
    //ComponentB* cB = new ComponentB();
    //ComponentC* cC = new ComponentC();

    //ConcreteMediator* mediator = new ConcreteMediator(cA, cB, cC);

    //cA->EventOne();

        Company* company = new Company();
        company->Work();
    }

    static void MementoExamples()
    {
        srand(time(nullptr));

        //MementoClient* client = new MementoClient();
        //client->ClientCode();

        Player* player = new Player();
        PlayerHistory* history = new PlayerHistory(player);

        for (int i{}; i < 5; i++)
        {
            player->Play();
            std::cout << "Player state: " << player->State() << "\n";
            history->Save();
        }

        history->Load();
        history->Load();
        history->Load();
        std::cout << "Player state: " << player->State() << "\n";
    }
};

