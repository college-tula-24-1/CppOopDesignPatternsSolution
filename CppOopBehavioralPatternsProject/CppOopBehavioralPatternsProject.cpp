#include <iostream>

#include "Command.h"

int main()
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


