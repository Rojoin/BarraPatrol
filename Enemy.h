﻿#pragma once
#include <string>

#include "Circle.h"

class Enemy
{
public:
    enum EnemyType
    {
        ground,
        groundObstacle,
        air,
        airSinusoidal
    };
    Enemy(int hp, Circle body, float speed, std::string name);
    Enemy();
    ~Enemy();
    void MoveRight();
    void MoveLeft();
    void SinusoidalMovement();
    void MoveUp();
    void MoveDown();
    void SetY(float y_);
    void SetX(float x_);
    void SetBody(Circle body_);
    Circle GetBody() const;
    void SetHp(int hpModifier);
    void SetSpeed(float speed_);
    void DrawEnemy() const;
private:
    int hp;
    bool isAlive;
    Circle body{};
    float speed;
    std::string name;
    
};
