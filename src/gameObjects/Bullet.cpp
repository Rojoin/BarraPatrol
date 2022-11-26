#include "Bullet.h"
#include "raylib.h"
#include <iostream>

#include "system/draw.h"


Bullet::Bullet()
{
    this->isActive = false;
    this->direction = {0, 0};
    this->rotation = 0;
    this->body = {0, 0, 0};
    this->speed = 0;
}

Bullet::~Bullet()
{
    std::cout << "Bullet was destroyed." << std::endl;
}

Vector2 Bullet::GetPosition() const
{
    return {body.position.x, body.position.y};
}

Circle Bullet::GetBody() const
{
    return body;
}

void Bullet::IsOutOfBounds()
{
    isActive = !(body.position.x > static_cast<float>(GetScreenWidth())) || !(body.position.y > static_cast<float>(GetScreenHeight()));
}

bool Bullet::IsActive() const
{
    return isActive;
}

void Bullet::Move()
{
    body.position.x += direction.x * speed * GetFrameTime();
    body.position.y += direction.y * speed * GetFrameTime();
}

void Bullet::draw() const
{
    const auto frameWidth = static_cast<float>(texture.width);
    const auto frameHeight = static_cast<float>(texture.height);
    Rectangle source{ 0,0,static_cast<float>(texture.width),static_cast<float>(texture.height) };
    Rectangle dest{ body.position.x  ,body.position.y,static_cast<float>(texture.width) * scale,static_cast<float>(texture.height) * scale };
    const Rectangle sourceRec = { 0,0,frameWidth,frameHeight};
    const Vector2 origin = {body.radius , body.radius};
    
    drawTexture(texture, source, dest, { static_cast<float>(texture.width) / 2.0f,static_cast<float>(texture.height) / 2.0f }, rotation, scale, WHITE);
}
