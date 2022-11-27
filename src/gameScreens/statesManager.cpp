#include "statesManager.h"

#include <ctime>

#include "creditsState.h"
#include "gameplayState.h"
#include "GameStates.h"
#include "menuState.h"
#include "optionsState.h"
#include "rulesState.h"

#include "system/draw.h"

extern Texture2D enemyTexture;
extern Texture2D creditsTexture;
extern Texture2D rulesTexture;

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
		statesRules(gameState);
		break;
	case GameStates::Options:
		statesOptions(gameState);

		break;
	case GameStates::Credits:
		statesCredits(gameState);

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
		drawRules();
		break;
	case GameStates::Options:
		drawOptions();

		break;
	case GameStates::Credits:
		drawCredits();

		break;
	case GameStates::Exit:
		break;
	}
	drawText("Version:0.4", 720, 720, 40, RED);
	EndDrawing();
}

void StatesManager::loadAudios()
{
}

void StatesManager::loadTextures()
{
	enemyTexture = LoadTexture("res/OVNI.png");
	rulesTexture  = LoadTexture("res/Rules.png");
	creditsTexture= LoadTexture("res/Credits.png");
	GenTextureMipmaps(&creditsTexture);
	SetTextureFilter(creditsTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
	GenTextureMipmaps(&rulesTexture);
	SetTextureFilter(rulesTexture, TEXTURE_FILTER_ANISOTROPIC_16X);

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


