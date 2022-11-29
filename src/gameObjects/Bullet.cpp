#include "Bullet.h"

#include "system/Circle.h"
#include "raylib.h"
#include "system/draw.h"
#if _DEBUG
#include <iostream>
#endif 

using namespace OBJ;

Texture2D bulletTexture;
Sound bulletSound;

Bullet::Bullet(float x, float y)
{
	this->activeState = false;
	this->texture = bulletTexture;
	this->sound = bulletSound;
	this->scale = 0.5f;
	this->direction = { 0, 0 };
	this->rotation = 0;
	this->body = { x, y , MAX_CIRCLE_RADIUS };
	this->speed = MAX_SPEED_FORCE;
}

Bullet::~Bullet()
{
	std::cout << "Bullet was destroyed." << std::endl;
}

Vector2 Bullet::getPosition()
{
	return { body.position.x, body.position.y };
}

Circle Bullet::getBody()
{
	return body;
}


bool Bullet::isActive()
{
	return activeState;
}

void Bullet::move()
{
	body.position.x += direction.x * speed * GetFrameTime();
	body.position.y += direction.y * speed * GetFrameTime();
}


void Bullet::draw()
{

	Rectangle source{ 0,0,static_cast<float>(texture.width),static_cast<float>(texture.height) };
	Rectangle dest{ body.position.x  ,body.position.y,static_cast<float>(texture.width)* scale,static_cast<float>(texture.height)* scale };

#if _DEBUG

	DrawCircle(static_cast<int>(body.position.x), static_cast<int>(body.position.y), body.radius, BLUE);
#endif
	drawTexture(texture, source, dest, { static_cast<float>(texture.width) / 2.0f,static_cast<float>(texture.height) / 2.0f }, rotation, scale, WHITE);


}

void Bullet::setActiveState(bool state)
{
	activeState = state;
}

void Bullet::setDirection(Vector2 dir)
{
	this->direction = dir;
	PlaySound(sound);
}

void Bullet::setPosition(float x, float y)
{
	body.position.x = x;
	body.position.y = y;
}
