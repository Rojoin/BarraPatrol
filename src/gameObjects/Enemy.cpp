#include "Enemy.h"

#include <iostream>
#include "raylib.h"

#include "system/Circle.h"
#include "system/draw.h"

Texture2D enemyTexture;

Enemy::Enemy()
{
    body = {400, 50,120,40};
    deadState = false;
    speed = 200;
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
    if (body.x - body.width >= 1280)
    {
        body.x = 0- body.width;
    }
}

void Enemy::moveLeft()
{
    body.x -= speed * GetFrameTime();
    if (body.x+body.width <=0)
    {
        body.x = 1280;
    }
}

void Enemy::sinusoidalMovement()
{
  static bool down = true;
    float  sinMov = sin(2.0f * GetFrameTime()*50) * 4;
	if (body.y > 400 && down)
	{
        down = false;
	}
  if (body.y < 0 && !down)
  {
      down = true;
  }
  if (down)
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


