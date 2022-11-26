#include "statesManager.h"

#include <ctime>

#include "GameStates.h"

StatesManager::StatesManager()
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

StatesManager::~StatesManager()
{
}

void StatesManager::initProgram()
{
	while (!WindowShouldClose() && isProgramRunning)
	{
		logicProgram();
		drawProgram();
	}
}

void StatesManager::exitProgram()
{
	unLoadResources();
	CloseWindow();
	CloseAudioDevice();
}



