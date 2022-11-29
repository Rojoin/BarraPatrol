#include "statesManager.h"

#include <time.h>
#include "creditsState.h"
#include "gameplayState.h"
#include "GameStates.h"
#include "initialAnimationScreen.h"
#include "menuState.h"
#include "optionsState.h"
#include "rulesState.h"
#include "system/draw.h"

extern Texture2D enemyTexture;
extern Texture2D creditsTexture;
extern Texture2D rulesTexture;
extern Texture2D playerTexture;
extern Texture2D bulletTexture;
extern Texture2D obstacleTexture;
extern Texture2D splashScreen;
extern Sound playerSound;
extern Sound bulletSound;
Texture2D paralaxBackground;
Texture2D paralaxMidground;
Music musicStream;
float scrollingBack = 0.0f;
float scrollingMid = 0.0f;

StatesManager::StatesManager()
{

	this->isProgramRunning = true;
	gameState = setGameState(GameStates::InitialAnimation);
	SetRandomSeed(static_cast<unsigned int>(time(NULL)));
	InitWindow(1024, 768, "Tactical Llama");
	InitAudioDevice();
	musicStream = LoadMusicStream("res/music.mp3");
	//HideCursor();
	SetMusicVolume(musicStream, 0.5);
	PlayMusicStream(musicStream);
	SetExitKey(NULL);
	SetWindowMinSize(1024, 768);
}

StatesManager::~StatesManager()
{

}

void StatesManager::runProgram()
{
	initProgram();
	exitProgram();
}

void StatesManager::initProgram()
{
	loadTextures();
	loadAudios();
	while (!WindowShouldClose() && isProgramRunning)
	{
		UpdateMusicStream(musicStream);
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
	scrollingBack -= 0.1f * GetFrameTime() * 800.0f;
	scrollingMid -= 0.5f * GetFrameTime() * 800.0f;
	if (scrollingBack <= -(paralaxBackground.width * 0.20f)) scrollingBack = 0;
	if (scrollingMid <= -(paralaxMidground.width * 0.20f)) scrollingMid = 0;
	updateScale();
	switch (gameState)
	{
	case GameStates::InitialAnimation:
		statesInitialAnimation(gameState);
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
	drawTexture(paralaxBackground, { scrollingBack , 0 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxBackground, { paralaxBackground.width * 0.20f + scrollingBack, 0 }, 0.0f, 0.20f, WHITE);

	drawTexture(paralaxMidground, { scrollingMid , 20 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxMidground, { (paralaxMidground.width * 0.20f + scrollingMid), 20 }, 0.0f, 0.20f, WHITE);
	switch (gameState)
	{
	case GameStates::InitialAnimation:
		drawInitialAnimation();
		break;
	case GameStates::Menu:
		drawMenu();
	drawText("Version:1.0", 720, 720, 40, RED);
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

	EndDrawing();
}

void StatesManager::loadAudios()
{
	playerSound = LoadSound("res/jump.wav");
	bulletSound = LoadSound("res/bullet.wav");
}

void StatesManager::loadTextures()
{
	paralaxBackground = LoadTexture("res/Cielo-01.png");
	paralaxMidground = LoadTexture("res/Montanas-01Edited.png");
	splashScreen = LoadTexture("res/SplashScreen.png");
	obstacleTexture = LoadTexture("res/Cactus_1.png");
	bulletTexture = LoadTexture("res/bullet.png");
	enemyTexture = LoadTexture("res/OVNI.png");
	playerTexture = LoadTexture("res/llamaSpriteSheet.png");
	rulesTexture = LoadTexture("res/Rules.png");
	creditsTexture = LoadTexture("res/Credits.png");

	GenTextureMipmaps(&creditsTexture);
	SetTextureFilter(creditsTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
	GenTextureMipmaps(&rulesTexture);
	SetTextureFilter(rulesTexture, TEXTURE_FILTER_ANISOTROPIC_16X);

}

void StatesManager::loadResources()
{
	loadTextures();
	loadAudios();
}

void StatesManager::unLoadAudio()
{
	UnloadSound(playerSound);
	UnloadSound(bulletSound);
	UnloadMusicStream(musicStream);
}

void StatesManager::unLoadTextures()
{
	UnloadTexture(paralaxBackground);
	UnloadTexture(paralaxMidground);
	UnloadTexture(splashScreen);
	UnloadTexture(obstacleTexture);
	UnloadTexture(bulletTexture);
	UnloadTexture(enemyTexture);
	UnloadTexture(playerTexture);
	UnloadTexture(rulesTexture);
	UnloadTexture(creditsTexture);
}

void StatesManager::unLoadResources()
{
	unLoadTextures();
	unLoadAudio();
}


