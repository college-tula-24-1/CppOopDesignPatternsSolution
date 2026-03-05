#include <iostream>
#include <time.h>

#include "Observable.h"

int main()
{
    srand(time(nullptr));

    //ObserverClient* client = new ObserverClient();
    //client->ClientCode();

    Buisness* buisness = new Buisness();
    buisness->BuisnessTrading();
}


