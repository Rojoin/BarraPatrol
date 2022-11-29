#include "button.h"

#include "raylib.h"
#include "system/draw.h"

const int SCREEN_SIZE_X = 1024;
const int SCREEN_SIZE_Y = 768;

void drawButton(Button button)
{
	float roundness = 10;
	int segments = 8;
	DrawRectangleRounded(button.rec, roundness, segments, button.color);

	drawText(button.buttonTittle,(int)button.rec.x, (int)(button.rec.y + (button.rec.height) / 3), 25, BLACK);
	if (button.isOverThisButton)
	{
		DrawRectangleRoundedLines(button.rec, roundness, segments, 5, BLACK);
	}

}
void drawButtonTranslucent(Button button)
{
	Color translucentButton = button.color;
	Color translucentFont = BLACK;
	translucentButton.a /= 2;
	translucentFont.a /= 2;
	float roundness = 10;
	int segments = 8;

	DrawRectangleRounded(button.rec, roundness, segments, translucentButton);

	drawText(button.buttonTittle, (int)button.rec.x , (int)(button.rec.y + (button.rec.height) / 3), (int)(25.1f *static_cast<float>(GetScreenHeight() / SCREEN_SIZE_Y)), translucentFont);

	if (button.isOverThisButton)
	{
		DrawRectangleRounded(button.rec, roundness, segments, button.color);
		drawText(button.buttonTittle, (int)button.rec.x , (int)(button.rec.y + (button.rec.height) / 3), (int)( 25.1f *static_cast<float>(GetScreenHeight() / SCREEN_SIZE_Y)), BLACK);
		DrawRectangleRoundedLines(button.rec, roundness, segments, 5, BLACK);
	}
}
Button createButton(const char* buttonTitle, Color color)
{
	Button button;

	button.rec = { static_cast<float>(GetScreenWidth() / 2 - buttonWidth / 2) ,  static_cast<float>(GetScreenHeight() / 3), buttonWidth * static_cast<float>(GetScreenWidth()) / SCREEN_SIZE_X , buttonHeight * static_cast<float>(GetScreenHeight()) / SCREEN_SIZE_Y };
	button.buttonTittle = buttonTitle;
	button.isSelected = false;
	button.isOverThisButton = false;
	button.color = color;

	return button;
}
Button createButton(float x, float y, const char* buttonTitle, Color color)
{
	Button button;

	button.rec = { x ,y , buttonWidth * static_cast<float>(GetScreenWidth()) / SCREEN_SIZE_X , buttonHeight * static_cast<float>(GetScreenHeight()) / SCREEN_SIZE_Y };
	button.buttonTittle = buttonTitle;
	button.isSelected = false;
	button.isOverThisButton = false;
	button.color = color;

	return button;
}
Button createButton(float x, float y, float width, float height, const char* buttonTitle, Color color)
{
	Button button;

	button.rec = { x ,y , width * static_cast<float>(GetScreenWidth()) / SCREEN_SIZE_X , height * static_cast<float>(GetScreenHeight()) / SCREEN_SIZE_Y };
	button.buttonTittle = buttonTitle;
	button.isSelected = false;
	button.isOverThisButton = false;
	button.color = color;

	return button;
}