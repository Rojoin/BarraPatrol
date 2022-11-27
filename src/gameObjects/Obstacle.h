#pragma once
#include "raylib.h"
class Obstacle
{
private:
	Rectangle rec;
	bool jumped;
	Texture2D texture;
	float scale;

public:
	Obstacle();
	~Obstacle();
	void reset();
	void changePosX();
	void draw();
	bool checkCharacterPosition(float x);
	bool hasBeenJumped();
	void setJumpedState(bool state);
	Rectangle getRec();
};