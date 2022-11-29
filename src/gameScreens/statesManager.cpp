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

using namespace GAME;

extern Texture2D enemyTexture;
extern Texture2D creditsTexture;
extern Texture2D rulesTexture;
extern Texture2D playerTexture;
extern Texture2D bulletTexture;
extern Texture2D obstacleTexture;
extern Texture2D splashScreen;
extern Sound playerSound;
extern Sound bulletSound;
static Texture2D paralaxBackground;
static Texture2D paralaxMidground;
static Music musicStream;
static float scrollingBack = 0.0f;
static float scrollingMid = 0.0f;
const float SCROLLING_SPEED = 800.0f;
const float WALLPAPER_SCALE = 0.20f;
const float MID_SCROLLIN_SPEED = 0.5f;
const float BACK_SCROLLIN_SPEED = 0.1f;
const int SCREEN_SIZE_X = 1024;
const int SCREEN_SIZE_Y = 768;
const float MAX_VOLUME = 0.5f;

StatesManager::StatesManager()
{
	this->isProgramRunning = true;
	gameState = setGameState(GameStates::InitialAnimation);
	
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
	SetRandomSeed(static_cast<unsigned int>(time(NULL)));
	InitWindow(SCREEN_SIZE_X, SCREEN_SIZE_Y, "Tactical Llama");
	InitAudioDevice();
	musicStream = LoadMusicStream("res/music.mp3");
	SetMusicVolume(musicStream, MAX_VOLUME);
	PlayMusicStream(musicStream);
	SetExitKey(NULL);
	SetWindowMinSize(SCREEN_SIZE_X, SCREEN_SIZE_Y);

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


	scrollingBack -= BACK_SCROLLIN_SPEED * GetFrameTime() * SCROLLING_SPEED;
	scrollingMid -= MID_SCROLLIN_SPEED * GetFrameTime() * SCROLLING_SPEED;
	if (scrollingBack <= -(paralaxBackground.width * WALLPAPER_SCALE)) scrollingBack = 0;
	if (scrollingMid <= -(paralaxMidground.width * WALLPAPER_SCALE)) scrollingMid = 0;
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
	drawTexture(paralaxBackground, { scrollingBack , 0 }, 0.0f, WALLPAPER_SCALE, WHITE);
	drawTexture(paralaxBackground, { paralaxBackground.width * WALLPAPER_SCALE + scrollingBack, 0 }, 0.0f, WALLPAPER_SCALE, WHITE);

	drawTexture(paralaxMidground, { scrollingMid , 20 }, 0.0f, WALLPAPER_SCALE, WHITE);
	drawTexture(paralaxMidground, { (paralaxMidground.width * WALLPAPER_SCALE + scrollingMid), 20 }, 0.0f, WALLPAPER_SCALE, WHITE);
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


