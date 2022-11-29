#include <string>


#include "GameStates.h"
#include "menuState.h"
#include "raylib.h"

#include "system/collisionFunctions.h"
#include "gameLogic/mouseInputs.h"
#include "system/button.h"
#include "system/draw.h"
#include "gameplayState.h"

Vector2 middleScreen = { GetScreenWidth() / 2.0f,GetScreenHeight() / 2.0f };


Button playButton = createButton("     PLAY", DARKGREEN);
Button play2PButton = createButton("   2PPLAY", DARKGREEN);
Button howToPlayButton = createButton("   RULES", YELLOW);
Button optionsButton = createButton("  OPTIONS ", YELLOW);
Button creditsButton = createButton("  CREDITS ", YELLOW);
Button exitButton = createButton("   EXIT", RED);


void statesMenu(GameStates& gamestate)
{

	middleScreen = { static_cast<float> (GetScreenWidth()) / 2.0f,static_cast<float>(GetScreenHeight()) / 2.0f };
	playButton = createButton(playButton.rec.width / 2, middleScreen.y - playButton.rec.height * 2, "   PLAY", DARKGREEN);
	play2PButton = createButton(play2PButton.rec.width / 2, playButton.rec.y + play2PButton.rec.height * 2, "   PLAY 2P", DARKGREEN);
	howToPlayButton = createButton(howToPlayButton.rec.width / 2, play2PButton.rec.y + howToPlayButton.rec.height * 2, howToPlayButton.buttonTittle, howToPlayButton.color);
	optionsButton = createButton(optionsButton.rec.width / 2, howToPlayButton.rec.y + optionsButton.rec.height * 2, optionsButton.buttonTittle, optionsButton.color);
	creditsButton = createButton(creditsButton.rec.width / 2, optionsButton.rec.y + creditsButton.rec.height * 2, creditsButton.buttonTittle, creditsButton.color);
	exitButton = createButton(exitButton.rec.width / 2, creditsButton.rec.y + exitButton.rec.height * 2, exitButton.buttonTittle, exitButton.color);
	Vector2 mousePoint = Inputs::getMouseInput();

	if (isPointRecColliding(mousePoint, playButton.rec))
	{
		playButton.isOverThisButton = true;


		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = GameStates::Game;
			initGame(false);
		}
	}
	else
	{
		playButton.isOverThisButton = false;
	}
	if (isPointRecColliding(mousePoint, play2PButton.rec))
	{
		play2PButton.isOverThisButton = true;


		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = GameStates::Game;
			initGame(true);
		}
	}
	else
	{
		play2PButton.isOverThisButton = false;
	}
	if (isPointRecColliding(mousePoint, howToPlayButton.rec))
	{
		howToPlayButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = setGameState(GameStates::Rules);
		}
	}
	else
	{
		howToPlayButton.isOverThisButton = false;
	}
	if (isPointRecColliding(mousePoint, optionsButton.rec))
	{
		optionsButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = setGameState(GameStates::Options);

		}
	}
	else
	{
		optionsButton.isOverThisButton = false;
	}

	if (isPointRecColliding(mousePoint, creditsButton.rec))
	{
		creditsButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = setGameState(GameStates::Credits);
		}
	}
	else
	{
		creditsButton.isOverThisButton = false;
	}
	if (isPointRecColliding(mousePoint, exitButton.rec))
	{
		exitButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = GameStates::Exit;
		}
	}
	else
	{
		exitButton.isOverThisButton = false;
	}

}
void drawMenu()
{
	int width = (GetScreenWidth());
	int height = (GetScreenHeight());
	drawButton(playButton);
	drawButton(play2PButton);
	drawButton(howToPlayButton);
	drawButton(optionsButton);
	drawButton(creditsButton);
	drawButton(exitButton);
	int fontSize = 14 * static_cast<int>(GetScreenHeight()) / 728;
	std::string titleScreen = "Tactical Llama";
	drawText(titleScreen.c_str(), width / 4 - static_cast<int>(titleScreen.length())* fontSize, (height / 8), fontSize * 8, BLACK);
}