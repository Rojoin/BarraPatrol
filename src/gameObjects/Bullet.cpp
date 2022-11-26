#include "Bullet.h"
#include "raylib.h"
#include <iostream>

Bullet::Bullet(Shooter shooter, Vector2 direction, Vector2 position, float radius, float rotation, float speed)
{
    this->shooter = shooter;
    this->direction = direction;
    this->rotation = rotation;
    this->body = {position.x, position.y, radius};
    this->speed = speed;
    isActive = true;
}

Bullet::Bullet()
{
    this->isActive = false;
    this->shooter = player;
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

void Bullet::Draw(Texture2D bulletTexture) const
{
    const auto frameWidth = static_cast<float>(bulletTexture.width);
    const auto frameHeight = static_cast<float>(bulletTexture.height);
    const Rectangle sourceRec = { 0,0,frameWidth,frameHeight};
    const Vector2 origin = {body.radius , body.radius};
    
    DrawTexturePro(bulletTexture, sourceRec, {body.position.x, body.position.y, body.radius*2, body.radius*2}, origin, rotation, RAYWHITE);

}
