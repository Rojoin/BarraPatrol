#pragma once
#include "raylib.h"

class Obstacle
{
private:
	Rectangle rec;
	bool jumped;
	Texture2D texture;
	float scale;
	const int SPAWN_POSITION_X = 1280;
	const int SPAWN_POSITION_y = 600;
	const int MAX_GRAVITY_FORCE = 200;

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