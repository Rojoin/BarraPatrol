#include "keyboardInputs.h"

#include "raylib.h"

bool Inputs::isKeyBoardKeyPressed(KeyboardKey key)
{
	return IsKeyPressed(key);
}

bool Inputs::isKeyBoardKeyDown(KeyboardKey key)
{
	return IsKeyDown(key);
}
