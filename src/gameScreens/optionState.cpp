#include "optionsState.h"

#include <raylib.h>

#include "gameStates.h"
#include "system/button.h"


Button backButton = createButton(" GO BACK", RED);
Button fullScreen;


void statesOptions(GameStates& gameStates)
{

	backButton = createButton(0, (float)GetScreenHeight() - backButton.rec.height * 2, backButton.buttonTittle, backButton.color);
	fullScreen = createButton(static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2), 200 , 60.0f * static_cast<float>(GetScreenHeight() / 768), "FullScreen", RED);
	
	Vector2 mousePoint = GetMousePosition();
	if (CheckCollisionPointRec(mousePoint, backButton.rec))
	{
		backButton.isOverThisButton = true;

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gameStates = setGameState(GameStates::Menu);
		}
	}
	else
	{
		backButton.isOverThisButton = false;
	}

	if (CheckCollisionPointRec(mousePoint, fullScreen.rec))
	{
		fullScreen.isOverThisButton = true;

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			ToggleFullscreen();
		}
	}
	else
	{
		fullScreen.isOverThisButton = false;
	}


	

}
void drawOptions()
{
	ClearBackground(BLACK);
	drawButton(fullScreen);
	drawButton(backButton);

}