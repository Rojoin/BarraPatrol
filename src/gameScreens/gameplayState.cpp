#include "gameplayState.h"
#if _DEBUG
#include <iostream>
#endif 

#include "gameLogic/gameLogic.h"
#include "gameLogic/keyboardInputs.h"
#include "gameLogic/mouseInputs.h"
#include "gameObjects/Enemy.h"
#include "gameObjects/Obstacle.h"
#include "system/draw.h"

#include "gameObjects/player.h"
#include "gameObjects/Bullet.h"
#include "system/button.h"
#include "system/collisionFunctions.h"


Player* character1;
Player* character2;
Obstacle* obstacle;

Enemy* enemy;
Enemy* enemy2;

Button pauseMenuButton;
Button continueMenuButton;
Button restartMenuButton;
Button exitMenuButton;

const char* playerScore;
const char* maxScore;
float highScore = 0.0f;
bool firstTime = true;
bool secondPlayerActivate = false;
bool isGamePaused = false;
bool isGameOver = false;

Texture2D paralaxNearForeground;


float scrollingFore = 0.0f;
float totalScore = 0.0f;

void unloadTextures();
void backToMenu();
extern Vector2 screenSize;
void stateGame(GameStates& gameStates)
{

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
				if (secondPlayerActivate)
				{
					initGame(true);
				}
				else
				{
					initGame();
				}
			}

		}
		else
		{
			restartMenuButton.isOverThisButton = false;
		}
		if (totalScore > highScore)
		{
			highScore = totalScore;
			if (SaveStorageValue(0, static_cast<int>(highScore)))
			{
			}
		}
	}
	else if (!isGamePaused)
	{

		scrollingFore -= 1.0f * GetFrameTime() * 800.0f * screenSize.x;

		enemy->sinusoidalMovement();
		enemy2->sinusoidalMovement();
		enemy->moveRight();
		enemy2->moveRight();
		obstacle->changePosX();

		if (scrollingFore <= -(paralaxNearForeground.width * 0.20f)) scrollingFore = 0;

		if (isPointRecColliding(Inputs::getMouseInput(), pauseMenuButton.rec))
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
		if (character1->isDead() != true)
		{
			if (Inputs::isKeyBoardKeyPressed(KEY_SPACE))
			{
				character1->jump();
			}
			if (Inputs::isKeyBoardKeyDown(KEY_A))
			{
				character1->moveLeft();
			}
			if (Inputs::isKeyBoardKeyDown(KEY_D))
			{
				character1->moveRight();
			}
			if (Inputs::isKeyBoardKeyPressed(KEY_W))
			{
				character1->ShootUp();
			}
			character1->update();
			character1->updateBullet();
	
			if (isBulletEnemyColliding(character1->getBullet(), enemy))
			{
				character1->getBullet()->setActiveState(false);
				character1->scoreUp(100);
				enemy->reset();

			}
			if (isBulletEnemyColliding(character1->getBullet(), enemy2))
			{
				character1->getBullet()->setActiveState(false);
				character1->scoreUp(100);
				enemy2->reset();

			}
			if (!isCharacterObstacleColliding(character1, obstacle))
			{
				if (obstacle->checkCharacterPosition(character1->getBody().x + character1->getBody().width / 2))
				{
					character1->scoreUp(100);
				}
			}
		
			character1->setDeadState(isCharacterObstacleColliding(character1, obstacle));
			isGameOver = character1->isDead();
		}
			totalScore = character1->getScore();
		if (secondPlayerActivate)
		{
			if (character2->isDead() != true)
			{
				if (Inputs::isKeyBoardKeyPressed(KEY_RIGHT_SHIFT))
				{
					character2->jump();
				}
				if (Inputs::isKeyBoardKeyDown(KEY_J))
				{
					character2->moveLeft();
				}
				if (Inputs::isKeyBoardKeyDown(KEY_L))
				{
					character2->moveRight();
				}
				if (Inputs::isKeyBoardKeyPressed(KEY_I))
				{
					character2->ShootUp();
				}
				character2->update();
				character2->updateBullet();
				if (isBulletEnemyColliding(character2->getBullet(), enemy))
				{
					character2->getBullet()->setActiveState(false);
					character2->scoreUp(100);
					enemy->reset();

				}
				if (isBulletEnemyColliding(character2->getBullet(), enemy2))
				{
					character2->getBullet()->setActiveState(false);
					character2->scoreUp(100);
					enemy2->reset();

				}
				if (!isCharacterObstacleColliding(character2, obstacle))
				{
					if (obstacle->checkCharacterPosition(character2->getBody().x + character2->getBody().width / 2))
					{
						character2->scoreUp(100);
					}
				}
				character2->setDeadState(isCharacterObstacleColliding(character2, obstacle));

				totalScore = character1->getScore() + character2->getScore();
			}

			isGameOver = character1->isDead() && character2->isDead();
		}
		
		
	}
	else if (isGamePaused)
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

				if (secondPlayerActivate)
				{
					initGame(true);
				}
				else
				{
					initGame();
				}

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
void initGame(bool secondPlayer)
{
	paralaxNearForeground = LoadTexture("res/Tierra-01.png");
	enemy = new Enemy();
	enemy2 = new Enemy(-400);
	character1 = new Player();
	if (secondPlayer)
	{
		character2 = new Player();
	}
	secondPlayerActivate = secondPlayer;
	totalScore = 0;
	obstacle = new Obstacle();
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
	highScore = static_cast<float>(LoadStorageValue(0));

}

void unloadTextures()
{

	UnloadTexture(paralaxNearForeground);
}

void drawScore()
{
	playerScore = TextFormat("Score:%0.0F", static_cast<double>(totalScore));
	maxScore = TextFormat("Max:%0.0F", static_cast<double>(highScore));
	int maxScoreMeasure = MeasureText(maxScore, 50);
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
	playerScore = TextFormat("Score:%0.0F", static_cast<double>(totalScore));
	int playerScoreMeasure = MeasureText(playerScore, 50);
	drawText(playerScore, GetScreenWidth() / 2 - playerScoreMeasure * (GetScreenWidth()) / 1024, GetScreenHeight() / 2 - playerScoreMeasure, 50 * static_cast<int>(GetScreenWidth() / 1024), BLACK);
	drawButton(restartMenuButton);
	drawButton(exitMenuButton);
}
void drawGame()
{
	if (!character1->isDead())
	{
		character1->draw();
		character1->drawBullet();
	}
	if (secondPlayerActivate)
	{
		if (!character2->isDead())
		{
			character2->draw();
			character2->drawBullet();
		}
	}
	obstacle->draw();
	drawButtonTranslucent(pauseMenuButton);
	drawTexture(paralaxNearForeground, { scrollingFore * screenSize.x, -120 * screenSize.x }, 0.0f, 0.20f * screenSize.x, WHITE);
	drawTexture(paralaxNearForeground, { paralaxNearForeground.width * 0.20f + scrollingFore * screenSize.x, -120 * screenSize.x }, 0.0f, 0.20f * screenSize.x, WHITE);
	enemy->draw();
	enemy2->draw();
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
