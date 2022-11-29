#include "creditsState.h"

#include <raylib.h>

#include "gameStates.h"
#include "system/draw.h"
#include "system/button.h"


Texture2D creditsTexture;
extern Button escapeButton;


const int SCREEN_SIZE_Y = 768;
void statesCredits(GameStates& gameStates)
{
	Vector2 mousePoint = GetMousePosition();
	escapeButton = createButton(0, (float)GetScreenHeight() - escapeButton.rec.height * 2, escapeButton.buttonTittle, escapeButton.color);
	if (CheckCollisionPointRec(mousePoint, escapeButton.rec))
	{
		escapeButton.isOverThisButton = true;

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gameStates = setGameState(GameStates::Menu);
		}
	}
	else
	{
		escapeButton.isOverThisButton = false;
	}
}
void drawCredits()
{

	static float width = static_cast<float>(GetScreenWidth());
	ClearBackground(BLACK);
	static float scale = 0.12f * GetScreenHeight() / SCREEN_SIZE_Y;
	drawTexture(creditsTexture, { width / 2.0f -(creditsTexture.width/2.0f)* scale, 0}, 0, scale, WHITE);
	drawButton(escapeButton);


}