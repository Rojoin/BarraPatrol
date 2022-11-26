#include "statesManager.h"

#include <ctime>

#include "GameStates.h"
#include "system/draw.h"

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

void StatesManager::logicProgram()
{
	mousePosX = GetMouseX();
	mousePosY = GetMouseY();
	updateScale();
	switch (gameState)
	{
	case GameStates::InitialAnimation:

		break;
	case GameStates::Menu:

		break;
	case GameStates::Game:

		break;
	case GameStates::Rules:

		break;
	case GameStates::Options:

		break;
	case GameStates::Credits:

		break;
	case GameStates::Exit:
		isProgramRunning = false;
		break;

	}
}
void StatesManager::drawProgram()
{
	BeginDrawing();
	ClearBackground(BLACK);
	switch (gameState)
	{
	case GameStates::InitialAnimation:

		break;
	case GameStates::Menu:

		break;
	case GameStates::Game:

		break;
	case GameStates::Rules:

		break;
	case GameStates::Options:

		break;
	case GameStates::Credits:

		break;
	case GameStates::Exit:
		break;
	}
	EndDrawing();
}


