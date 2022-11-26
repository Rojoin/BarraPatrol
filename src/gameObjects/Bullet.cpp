#include "Bullet.h"
#include "raylib.h"
#include <iostream>

#include "system/draw.h"

Texture2D bulletTexture;
Sound bulletSound;
Bullet::Bullet()
{
    this->activeState = false;
    this->texture = bulletTexture;
    this->sound = bulletSound;
    this->scale = 1.0f;
    this->direction = {0, 90};
    this->rotation = 0;
    this->body = {0, 0 , 10 };
    this->speed = 300;
}

Bullet::~Bullet()
{
    std::cout << "Bullet was destroyed." << std::endl;
}

Vector2 Bullet::getPosition() const
{
    return {body.position.x, body.position.y};
}

Circle Bullet::getBody() const
{
    return body;
}

void Bullet::isOutOfBounds()
{
    activeState = !(body.position.x > static_cast<float>(GetScreenWidth())) || !(body.position.y > static_cast<float>(GetScreenHeight()));
}

bool Bullet::isActive() const
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
    const auto frameWidth = static_cast<float>(texture.width);
    const auto frameHeight = static_cast<float>(texture.height);
    Rectangle source{ 0,0,static_cast<float>(texture.width),static_cast<float>(texture.height) };
    Rectangle dest{ body.position.x  ,body.position.y,static_cast<float>(texture.width) * scale,static_cast<float>(texture.height) * scale };
    const Rectangle sourceRec = { 0,0,frameWidth,frameHeight};
    const Vector2 origin = {body.radius , body.radius};
    DrawCircle(static_cast<int>(body.position.x), static_cast<int>(body.position.y), body.radius, BLUE);
    drawTexture(texture, source, dest, { static_cast<float>(texture.width) / 2.0f,static_cast<float>(texture.height) / 2.0f }, rotation, scale, WHITE);
}
