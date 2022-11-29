#include "Enemy.h"

#if _DEBUG
#include <iostream>
#endif 

#include "raylib.h"
#include "system/Circle.h"
#include "system/draw.h"

Texture2D enemyTexture;

Enemy::Enemy()
{
    body = {SPAWN_POSITION_X, SPAWN_POSITION_Y,120,40};
    deadState = false;
    speed = MAX_SPEED_FORCE;
    facingDown = true;
    texture = enemyTexture;
    scale = 0.10f;
}

Enemy::Enemy(float offSetX)
{
    body = { SPAWN_POSITION_X+offSetX, SPAWN_POSITION_Y_OFFSET,120,40 };
    deadState = false;
    speed = MAX_SPEED_FORCE;
    facingDown = true;
    texture = enemyTexture;
    scale = 0.10f;
}


Enemy::~Enemy()
{
    std::cout << "Enemy has been destoyed." << std::endl;
}

void Enemy::moveRight()
{
    body.x += speed * GetFrameTime();
    if (body.x - body.width >= MAX_SCREEN_SIZE)
    {
        body.x = 0- body.width;
    }
}

void Enemy::moveLeft()
{
    body.x -= speed * GetFrameTime();
    if (body.x+body.width <=0)
    {
        body.x = MAX_SCREEN_SIZE;
    }
}

void Enemy::reset()
{
    body.x = 0-texture.width*scale;
    
}

void Enemy::sinusoidalMovement()
{

    float sinMov = sin(2.0f * GetFrameTime()* MAX_SINMOV_SPEED) * MAGNITUDE;
	if (body.y > MAX_POSITION_Y && facingDown)
	{
        facingDown = false;
	}
  if (body.y < 0 && !facingDown)
  {
      facingDown = true;
  }
  if (facingDown)
  {
      body.y += sinMov;
  }
  else
  {
      body.y -= sinMov;
  }
 
}

Rectangle Enemy::getBody()
{
    return body;
}


void Enemy::draw()
{
    Rectangle source{ 0,0,(float)texture.width,(float)texture.height };
    Rectangle dest{ body.x ,body.y,(float)texture.width * scale ,(float)texture.height * scale };
#if _DEBUG
    DrawRectangleRec(body, RED);
#endif
    drawTexture(texture, source, dest, { static_cast<float>(texture.width) / 16.0f,static_cast<float>(texture.height) / 4.0f }, 0, scale , WHITE);

}


