#include "Obstacle.h"
#include "raylib.h"

Obstacle::Obstacle()
{
	rec = { 1280,600,75 ,150 };
	jumped = false;
}
Obstacle::~Obstacle()
{

}

void Obstacle::reset()
{
	rec = { 1280,600,75 ,150 };
	jumped = false;
}

void Obstacle::changePosX()
{
	rec.x -= 200 * GetFrameTime();
	if (rec.x < 0)
	{
		rec.x = (float)GetScreenWidth();
		setJumpedState(false);
	}
}

void Obstacle::draw()
{
	DrawRectangle((int)rec.x, (int)rec.y, (int)rec.width, (int)rec.height, BLUE);
}

bool Obstacle::checkCharacterPosition(float x)
{
	if (x > this->rec.x && !jumped)
	{
		setJumpedState(true);
		return true;
	}
	else
	{
		return false;
	}
}

bool Obstacle::hasBeenJumped()
{
	return jumped;
}

void Obstacle::setJumpedState(bool state)
{
	jumped = state;
}

Rectangle Obstacle::getRec()
{
	return rec;
}

