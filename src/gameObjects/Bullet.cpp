#include "Bullet.h"
#include "raylib.h"
#include <iostream>

#include "system/draw.h"

Texture2D bulletTexture;
Sound bulletSound;
Bullet::Bullet(float x, float y)
{
    this->activeState = false;
    this->texture = bulletTexture;
    this->sound = bulletSound;
    this->scale = 1.0f;
    this->direction = {0, 0};
    this->rotation = 0;
    this->body = {x, y , 10 };
    this->speed = 500;
}

Bullet::~Bullet()
{
    std::cout << "Bullet was destroyed." << std::endl;
}

Vector2 Bullet::getPosition() 
{
    return {body.position.x, body.position.y};
}

Circle Bullet::getBody() 
{
    return body;
}

void Bullet::isOutOfBounds()
{
    activeState = !(body.position.x > static_cast<float>(GetScreenWidth())) || !(body.position.y > static_cast<float>(GetScreenHeight()));
}

bool Bullet::isActive() 
{
    return activeState;
}

void Bullet::move()
{
    body.position.x += direction.x * speed * GetFrameTime();  //Agregar multiplicador por screen
    body.position.y += direction.y * speed * GetFrameTime();  //Agregar multiplicador por screen
}

void Bullet::draw() const
{
 
    DrawCircle(static_cast<int>(body.position.x), static_cast<int>(body.position.y), body.radius, BLUE);
  
}

void Bullet::setActiveState(bool state)
{
    activeState = state;
}

void Bullet::setDirection(Vector2 dir)
{
    this->direction = dir;
}

void Bullet::setPosition(float x, float y)
{
    body.position.x = x;
    body.position.y = y;
}
