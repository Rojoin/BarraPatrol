#include "gameplayState.h"
#include <iostream>

#include "gameLogic/gameLogic.h"
#include "gameLogic/keyboardInputs.h"
#include "gameObjects/Enemy.h"
#include "gameObjects/Obstacle.h"
#include "system/draw.h"

#include "gameObjects/player.h"


Player* character = new Player();
Obstacle* obstacle = new Obstacle();
Enemy* enemy;

const char* playerScore;
const char* maxScore;
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
		if (Inputs::isKeyBoardKeyDown(KEY_A))
		{
			character->moveLeft();
		}
		if (Inputs::isKeyBoardKeyDown(KEY_D))
		{
			character->moveRight();
		}
		if (Inputs::isKeyBoardKeyPressed(KEY_W))
		{
			character->ShootUp();
		}
		enemy->sinusoidalMovement();
		enemy->moveRight();
		character->update();
		character->updateBullet();
	obstacle->changePosX();
		if (isBulletEnemyColliding(character->getBullet(),enemy))
		{
			character->getBullet()->setActiveState(false);
			character->scoreUp(100);
			delete enemy;//cambiar por metodo reset

		}
	
	}
	else
	{
		gameStates = setGameState(GameStates::Menu);
		delete character;
		obstacle->reset();
		firstTime = true;
		unloadTextures();
	}
	character->setDeadState(isCharacterObstacleColliding(character, obstacle));
}

void backToMenu(GameStates& gameStates)
{
	if (IsKeyDown(KEY_ESCAPE))
	{
		gameStates = setGameState(GameStates::Menu);
		delete character;
		obstacle->reset();
		firstTime = true;
		unloadTextures();
	}
}
void initTextures()
{
	paralaxBackground = LoadTexture("res/Cielo-01.png");
	paralaxMidground = LoadTexture("res/Montanas-01Edited.png");
	paralaxNearForeground = LoadTexture("res/Tierra-01.png");
	 enemy = new Enemy();
}

void unloadTextures()
{
	UnloadTexture(paralaxBackground);
	UnloadTexture(paralaxMidground);
	UnloadTexture(paralaxNearForeground);
}

void drawScore()
{
	 playerScore = TextFormat("Score:%0.0F", static_cast<double>(character->getScore()));
	maxScore = TextFormat("Max:%0.0F", static_cast<double>(character->getScore()));
	int maxScoreMeasure = MeasureText( maxScore, 50);
	drawText(playerScore, 0, 0, 50 * static_cast<int>(GetScreenWidth() / 1024), BLACK);
	drawText(maxScore, GetScreenWidth() - maxScoreMeasure * 1 * (GetScreenWidth()) / 1024, 0, 50 * (GetScreenHeight()) / 768, BLACK);
}

void drawGame()
{
	drawTexture(paralaxBackground, { scrollingBack, 0 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxBackground, { paralaxBackground.width *  0.20f + scrollingBack, 0 }, 0.0f, 0.20f, WHITE);

	drawTexture(paralaxMidground, { scrollingMid, 20 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxMidground, { (paralaxMidground.width *0.20f + scrollingMid), 20 }, 0.0f, 0.20f, WHITE);

	character->draw();
	character->drawBullet();
	obstacle->draw();
	drawTexture(paralaxNearForeground, { scrollingFore, -120 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxNearForeground, { paralaxNearForeground.width* 0.20f + scrollingFore, -120 }, 0.0f, 0.20f, WHITE);
	enemy->draw();
	drawScore();


}
