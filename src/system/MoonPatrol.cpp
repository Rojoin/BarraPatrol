#include "gameScreens/menu.h"
#include "gameScreens/statesManager.h"

int main()
{
    //Menu();
    StatesManager* statesManager = new StatesManager();

    statesManager->initProgram();
    statesManager->exitProgram();
    return 0;
}
