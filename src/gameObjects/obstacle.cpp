#include "Obstacle.h"

#include "raylib.h"
#include "system/draw.h"

using namespace OBJ;

Texture2D obstacleTexture;

Obstacle::Obstacle()
{
	rec = { SPAWN_POSITION_X,SPAWN_POSITION_y,80 ,600 };
	jumped = false;
	texture = obstacleTexture;
	scale = 0.07f;
}
Obstacle::~Obstacle()
{

}

void Obstacle::reset()
{
	rec = { SPAWN_POSITION_X,SPAWN_POSITION_y,80 ,600 };
	jumped = false;
}

void Obstacle::changePosX()
{
	rec.x -= MAX_GRAVITY_FORCE * GetFrameTime();
	if (rec.x < 0 - rec.width)
	{
		rec.x = (float)GetScreenWidth();
		setJumpedState(false);
	}
}

void Obstacle::draw()
{
	Rectangle source{ 0,0,(float)texture.width,(float)texture.height };
	Rectangle dest{ rec.x -rec.width/2*scale/4,rec.y- texture.height / 2 * scale/2 ,(float)texture.width * scale ,(float)texture.height  * scale };

#if _DEBUG
	DrawRectangle((int)rec.x, (int)rec.y, (int)rec.width, (int)rec.height, BLUE);
#endif
	drawTexture(texture, source, dest, { static_cast<float>(texture.width) /2 *scale,static_cast<float>(texture.height) / 2.0f*scale }, 0, scale, WHITE);
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

