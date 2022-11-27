#include "gameplayState.h"

#include <iostream>

#include "gameLogic/keyboardInputs.h"
#include "system/draw.h"

#include "gameObjects/player.h"
#include "gameScreens/gameStates.h"

Player* character = new Player();
//Obstacle* obstacle = new Obstacle();

bool firstTime = true;
Texture2D paralaxBackground;
Texture2D paralaxMidground;
Texture2D paralaxNearForeground;
float scrollingBack = 0.0f;
float scrollingMid = 0.0f;
float scrollingFore = 0.0f;
void initTextures();
void unloadTextures();
void backToMenu(GameStates& gameStates);

void stateGame(GameStates& gameStates)
{
	scrollingBack -= 0.1f* GetFrameTime() * 800.0f;
	scrollingMid -= 0.5f * GetFrameTime() * 800.0f;
	scrollingFore -= 1.0f* GetFrameTime() * 800.0f;

	if (firstTime)
	{
		initTextures();
		firstTime = false;
	}
	if (scrollingBack <= -(paralaxBackground.width  * 0.20f)) scrollingBack = 0;
	if (scrollingMid <= -(paralaxMidground.width  * 0.20f)) scrollingMid = 0;
	if (scrollingFore <= -(paralaxNearForeground.width  * 0.20f)) scrollingFore = 0;

	backToMenu(gameStates);
	if (character->isDead() != true)
	{
		if (Inputs::isKeyBoardKeyPressed(KEY_SPACE))
		{
			character->jump();
		}
		character->update();
	//obstacle->changePosX();
	}
	else
	{
		gameStates = setGameState(GameStates::Menu);
		delete character;
		firstTime = true;
		unloadTextures();
	}
	//character->setDeadState(isCharacterObstacleColliding(character, obstacle));
}

void backToMenu(GameStates& gameStates)
{
	if (IsKeyDown(KEY_ESCAPE))
	{
		gameStates = setGameState(GameStates::Menu);
		delete character;
		//obstacle->reset();
		firstTime = true;
		unloadTextures();
	}
}
void initTextures()
{
	paralaxBackground = LoadTexture("res/Cielo-01.png");
	paralaxMidground = LoadTexture("res/Montanas-01Edited.png");
	paralaxNearForeground = LoadTexture("res/Tierra-01.png");
}

void unloadTextures()
{
	UnloadTexture(paralaxBackground);
	UnloadTexture(paralaxMidground);
	UnloadTexture(paralaxNearForeground);
}
void drawGame()
{
	drawTexture(paralaxBackground, { scrollingBack, 0 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxBackground, { paralaxBackground.width *  0.20f + scrollingBack, 0 }, 0.0f, 0.20f, WHITE);

	drawTexture(paralaxMidground, { scrollingMid, 20 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxMidground, { (paralaxMidground.width *0.20f + scrollingMid), 20 }, 0.0f, 0.20f, WHITE);

	character->draw();
	//obstacle->draw();
	
	drawTexture(paralaxNearForeground, { scrollingFore, -120 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxNearForeground, { paralaxNearForeground.width* 0.20f + scrollingFore, -120 }, 0.0f, 0.20f, WHITE);
	


}
