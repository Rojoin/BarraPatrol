#include  "initialAnimationScreen.h"


#include <raylib.h>
#include <string>
#include  "gameStates.h"
#include "system/draw.h"



Texture2D splashScreen;
float normalizedTime = 0.0f;
float timePlayed = 0.0f;
float maxTime = 12.0f;
int currentAlpha = 0;
int maxAlpha = 255;
Color transparency ={255,255,255,0};
void statesInitialAnimation(GameStates& gamestate)
{
	normalizedTime = timePlayed / maxTime;
	timePlayed += GetFrameTime();

	if (timePlayed < maxTime/2 && normalizedTime <0.5f)
	{
		currentAlpha = static_cast<int>(normalizedTime *255*4);
		if (currentAlpha == maxAlpha)
		{
			gamestate =setGameState(GameStates::Menu);
		}
	}
	transparency.a = static_cast<unsigned char>(currentAlpha);
}

void drawInitialAnimation()
{
	int width = (GetScreenWidth());
	int height = (GetScreenHeight());
	ClearBackground(BLACK);
	int fontSize = 3 * width / 350;
	const std::string GamePresentTittle = "Rojoin presents:";
	drawText(GamePresentTittle.c_str(), width / 2 - static_cast<int>(GamePresentTittle.length()) * fontSize, height / 40, fontSize * 8, DARKBROWN);
	drawTexture(splashScreen, {(float) width/4,(float)height/4 }, 0, 0.5f, transparency);
}
