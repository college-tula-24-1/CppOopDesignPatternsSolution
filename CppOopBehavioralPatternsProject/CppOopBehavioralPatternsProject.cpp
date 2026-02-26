#include <iostream>
#include <time.h>

#include "Memento.h"

int main()
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


