#include "gameplayState.h"
#include <iostream>

#include "gameLogic/gameLogic.h"
#include "gameLogic/keyboardInputs.h"
#include "gameLogic/mouseInputs.h"
#include "gameObjects/Enemy.h"
#include "gameObjects/Obstacle.h"
#include "system/draw.h"

#include "gameObjects/player.h"
#include "system/button.h"
#include "system/collisionFunctions.h"


Player* character ;
Obstacle* obstacle;
Enemy* enemy;

Button pauseMenuButton;
Button continueMenuButton;
Button restartMenuButton;
Button exitMenuButton;

const char* playerScore;
const char* maxScore;
bool firstTime = true;
bool isGamePaused = false;
bool isGameOver = false;
Texture2D paralaxBackground;
Texture2D paralaxMidground;
Texture2D paralaxNearForeground;
float scrollingBack = 0.0f;
float scrollingMid = 0.0f;
float scrollingFore = 0.0f;
void initTextures();
void unloadTextures();
void backToMenu();

void stateGame(GameStates& gameStates)
{
	scrollingBack -= 0.1f* GetFrameTime() * 800.0f;
	scrollingMid -= 0.5f * GetFrameTime() * 800.0f;
	scrollingFore -= 1.0f* GetFrameTime() * 800.0f;

	if (firstTime)
	{
		initTextures();
		
	}
	if (scrollingBack <= -(paralaxBackground.width  * 0.20f)) scrollingBack = 0;
	if (scrollingMid <= -(paralaxMidground.width  * 0.20f)) scrollingMid = 0;
	if (scrollingFore <= -(paralaxNearForeground.width  * 0.20f)) scrollingFore = 0;

	backToMenu();
	if (isGameOver)
	{
		if (isPointRecColliding(Inputs::getMouseInput(), exitMenuButton.rec))
		{
			exitMenuButton.isOverThisButton = true;


			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{

				gameStates = setGameState(GameStates::Menu);
			}
		}
		else
		{
			exitMenuButton.isOverThisButton = false;
		}
		if (isPointRecColliding(Inputs::getMouseInput(), restartMenuButton.rec))
		{
			restartMenuButton.isOverThisButton = true;

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{

				firstTime = true;
			}

		}
		else
		{
			restartMenuButton.isOverThisButton = false;
		}
	}
	else if (!isGamePaused)
	{
		if(isPointRecColliding(Inputs::getMouseInput(), pauseMenuButton.rec))
		{
			pauseMenuButton.isOverThisButton = true;


			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{

				isGamePaused = true;
			}

		}
	else
	{
		pauseMenuButton.isOverThisButton = false;
	}
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
			if (isBulletEnemyColliding(character->getBullet(), enemy))
			{
				character->getBullet()->setActiveState(false);
				character->scoreUp(100);
				enemy->reset();

			}
		}

		if (!isCharacterObstacleColliding(character, obstacle))
		{
			if (obstacle->checkCharacterPosition(character->getBody().x + character->getBody().width / 2))
			{
				character->scoreUp(100);
			}
		}
		character->setDeadState(isCharacterObstacleColliding(character, obstacle));
		isGameOver = character->isDead();
	}
	else if (isGamePaused)
	{

		if (isPointRecColliding(Inputs::getMouseInput(), exitMenuButton.rec))
		{
			exitMenuButton.isOverThisButton = true;


			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{

				gameStates =setGameState(GameStates::Menu);
			}

		}
		else
		{
			exitMenuButton.isOverThisButton = false;
		}
		if (isPointRecColliding(Inputs::getMouseInput(), continueMenuButton.rec))
		{
			continueMenuButton.isOverThisButton = true;


			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{

				isGamePaused = false;
			}

		}
		else
		{
			continueMenuButton.isOverThisButton = false;
		}
		if (isPointRecColliding(Inputs::getMouseInput(), restartMenuButton.rec))
		{
			restartMenuButton.isOverThisButton = true;


			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{

				firstTime = true;

			}

		}
		else
		{
			restartMenuButton.isOverThisButton = false;
		}

	}
}

void backToMenu()
{
	if (IsKeyDown(KEY_ESCAPE))
	{
		isGamePaused = true;
	}
}
void initTextures()
{
	paralaxBackground = LoadTexture("res/Cielo-01.png");
	paralaxMidground = LoadTexture("res/Montanas-01Edited.png");
	paralaxNearForeground = LoadTexture("res/Tierra-01.png");
	 enemy = new Enemy();
	 character = new Player();
	 obstacle= new Obstacle();
	 firstTime = false;
	 isGameOver = false;
	 isGamePaused = false;
	 float width = static_cast<float>(GetScreenWidth());
	 float height = static_cast<float>(GetScreenHeight());
	 isGamePaused = false;
	 continueMenuButton = createButton(width / 2 - buttonWidth / 2 * static_cast<float>(GetScreenWidth()) / 1024, height / 2 - height / 8 * static_cast<float>(GetScreenHeight()) / 768, buttonWidth, buttonHeight, " CONTINUE", DARKGREEN);
	 restartMenuButton = createButton(width / 3 + width / 4 - buttonWidth / 2 * static_cast<float>(GetScreenWidth()) / 1024, height / 2.0f - buttonHeight * static_cast<float>(GetScreenHeight()) / 768, buttonWidth, buttonHeight, " RESTART", DARKPURPLE);
	 exitMenuButton = createButton(width / 3 + width / 8 - buttonWidth * static_cast<float>(GetScreenWidth()) / 1024, height / 2.0f - buttonHeight * static_cast<float>(GetScreenHeight()) / 768, buttonWidth, buttonHeight, "   EXIT", RED);
	 pauseMenuButton = createButton(width / 2 - buttonWidth / 2 * static_cast<float>(GetScreenWidth()) / 1024, 0 + buttonHeight / 2 * static_cast<float>(GetScreenHeight()) / 768, buttonWidth, buttonHeight, "  PAUSE", DARKGREEN);
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

void drawPauseMenu()
{


	drawButton(continueMenuButton);
	drawButton(restartMenuButton);
	drawButton(exitMenuButton);
}
void drawEndMenu()
{

	playerScore = TextFormat("Score:%0.0F", static_cast<double>(character->getScore()));
	int playerScoreMeasure = MeasureText(playerScore, 50);
	drawText(playerScore, GetScreenWidth() / 2 - playerScoreMeasure  *(GetScreenWidth()) / 1024, GetScreenHeight() / 2 - playerScoreMeasure, 50 * static_cast<int>(GetScreenWidth() / 1024), BLACK);
	drawButton(restartMenuButton);
	drawButton(exitMenuButton);
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
	drawButtonTranslucent(pauseMenuButton);
	drawTexture(paralaxNearForeground, { scrollingFore, -120 }, 0.0f, 0.20f, WHITE);
	drawTexture(paralaxNearForeground, { paralaxNearForeground.width* 0.20f + scrollingFore, -120 }, 0.0f, 0.20f, WHITE);
	enemy->draw();
	drawScore();
	if (isGameOver)
	{
		drawEndMenu();
	}
	else if (isGamePaused)
	{
		drawPauseMenu();
	}


}
