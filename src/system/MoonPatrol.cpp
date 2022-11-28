
#include "gameScreens/statesManager.h"

int main()
{
    //Menu();
    StatesManager* statesManager = new StatesManager();

    statesManager->initProgram();
    statesManager->exitProgram();
    delete statesManager;
    return 0;
}
