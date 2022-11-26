#include "statesManager.h"

#include <ctime>

#include "GameStates.h"

statesManager::statesManager()
{

	this->isProgramRunning = true;
	setGameState(GameStates::Menu);
	SetRandomSeed(static_cast<unsigned int>(time(NULL)));
	InitWindow(1024, 768, "Tactical Llama");
	HideCursor();
	InitAudioDevice();
	loadResources();
	SetExitKey(NULL);
	SetWindowMinSize(1024, 768);
}

statesManager::~statesManager()
{
}

void statesManager::initProgram()
{
	while (!WindowShouldClose() && isProgramRunning)
	{
		logicProgram();
		drawProgram();
	}

}

void statesManager::exitProgram()
{
	unLoadResources();
	CloseWindow();
	CloseAudioDevice();
}


