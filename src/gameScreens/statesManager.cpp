#include "statesManager.h"

#include <ctime>

#include "gameplayState.h"
#include "GameStates.h"
#include "menuState.h"

#include "system/draw.h"

extern Texture2D enemyTexture;
StatesManager::StatesManager()
{

	this->isProgramRunning = true;
	gameState = setGameState(GameStates::Menu);
	SetRandomSeed(static_cast<unsigned int>(time(NULL)));
	InitWindow(1024, 768, "Tactical Llama");
	//HideCursor();
	InitAudioDevice();
	SetExitKey(NULL);
	SetWindowMinSize(1024, 768);
}

StatesManager::~StatesManager()
{
}

void StatesManager::initProgram()
{
	loadTextures();
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
		statesMenu(gameState);
		break;
	case GameStates::Game:
		stateGame(gameState);
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
	ClearBackground(WHITE);
	switch (gameState)
	{
	case GameStates::InitialAnimation:

		break;
	case GameStates::Menu:
		drawMenu();
		break;
	case GameStates::Game:
		drawGame();
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

void StatesManager::loadAudios()
{
}

void StatesManager::loadTextures()
{
	enemyTexture = LoadTexture("res/OVNI.png");
}

void StatesManager::loadResources()
{
}

void StatesManager::unLoadAudio()
{
}

void StatesManager::unLoadTextures()
{
}

void StatesManager::unLoadResources()
{
}


