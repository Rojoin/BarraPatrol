#include  "rulesState.h"

#include <raylib.h>

#include "gameStates.h"
#include "system/draw.h"
#include "system/button.h"


Button escapeButton = createButton(" GO BACK", RED);
Texture2D rulesTexture;
void statesRules(GameStates& gameStates)
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
void drawRules()
{

	float width = static_cast<float>(GetScreenWidth());
	ClearBackground(BLACK);
	float scale = 0.12f * GetScreenHeight() / 768;

	drawTexture(rulesTexture, { width / 2.0f - (rulesTexture.width / 2.0f) * scale, 0 }, 0, scale, WHITE);
	drawButton(escapeButton);


}