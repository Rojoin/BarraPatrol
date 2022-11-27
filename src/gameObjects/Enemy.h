#pragma once
#include "raylib.h"
#include <string>

#include "system/Circle.h"

class Enemy
{
public:
   

    Enemy();
    ~Enemy();
    void moveRight();
    void moveLeft();
    void sinusoidalMovement();
    Rectangle getBody();


    void draw();

private:
    bool deadState;
    Rectangle body{};
    float speed;
    Texture2D texture;
    float scale;
};
