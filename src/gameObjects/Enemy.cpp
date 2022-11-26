﻿#include "Enemy.h"

#include <iostream>
#include "raylib.h"

#include "system/Circle.h"

Enemy::Enemy()
{
    hp = 3;
    body = {
        static_cast<float>(GetScreenWidth()) / 2.f, static_cast<float>(GetScreenHeight()) / 2,
        static_cast<float>(GetScreenWidth()) / 30
    };
    deadState = true;
    speed = static_cast<float>(GetScreenWidth()) / 7.f;
    name = "GenericEnemy";
    type = ground;
}

Enemy::Enemy(int hp, Circle body, float speed, std::string name, EnemyType type)
{
    this->hp = hp;
    deadState = true;
    this->body = body;
    this->speed = speed;
    this->name = name;
    this->type = type;
}

Enemy::~Enemy()
{
    std::cout << "Enemy has been destoyed." << std::endl;
}

void Enemy::MoveRight()
{
    body.position.x += speed * GetFrameTime();
}

void Enemy::MoveLeft()
{
    body.position.x -= speed * GetFrameTime();
}

void Enemy::SinusoidalMovement()
{
    body.position.y += sin(body.position.x / 6) * GetFrameTime() * static_cast<float>(GetScreenWidth()) / 2;
}

void Enemy::MoveUp()
{
    body.position.x -= speed * GetFrameTime();
}

void Enemy::MoveDown()
{
    body.position.y += speed * GetFrameTime();
}

void Enemy::SetY(float y_)
{
    body.position.y = y_;
}

void Enemy::SetX(float x_)
{
    this->body.position.x = x_;
}

void Enemy::SetBody(Circle body_)
{
    this->body = body_;
}

Circle Enemy::getBody() const
{
    return body;
}

void Enemy::SetHp(int hpModifier)
{
    this->hp += hpModifier;
}

void Enemy::SetSpeed(float speed_)
{
    this->speed = speed_;
}

void Enemy::Draw(Texture2D bike) const
{
    const Rectangle bikeRec = {0,0, static_cast<float>(bike.width), static_cast<float>(bike.height)};
    DrawTextureRec(bike, bikeRec, {body.position.x, body.position.y-bikeRec.height/2}, RAYWHITE);
    //DrawCircle(static_cast<int>(body.x), static_cast<int>(body.y), body.radius, BLACK);
}

Enemy::EnemyType Enemy::GetType() const
{
    return type;
}
