
#include "gameScreens/statesManager.h"
using namespace GAME;
int main()
{
    StatesManager* statesManager = new StatesManager();
    statesManager->runProgram();
    delete statesManager;
    return 0;
}
