#include "keyboardInputs.h"
#include "raylib.h"
bool Inputs::isKeyBoardKeyPressed(KeyboardKey key)
{
	return IsKeyDown(key);
}
