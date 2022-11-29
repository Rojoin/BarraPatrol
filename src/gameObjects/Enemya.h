#pragma once
#include "raylib.h"

#include "system/Circle.h"

namespace OBJ
{

class Enemy
{
public:
   

    Enemy();
    Enemy(float offSetX);
    ~Enemy();
    void moveRight();
    void moveLeft();
    void reset();
    void sinusoidalMovement();
    Rectangle getBody();
    void draw();

private:
    bool facingDown;
    bool deadState;
    Rectangle body{};
    float speed;
    Texture2D texture;
    float scale;
    const float MAX_SPEED_FORCE = 200.0f;
    const float SPAWN_POSITION_X = 400.0f;
    const float SPAWN_POSITION_Y = 50;
    const float SPAWN_POSITION_Y_OFFSET = 400.0f;
    const float MAX_SCREEN_SIZE = 1280;
    const float MAX_POSITION_Y = 400.0f;
    const int MAGNITUDE = 4;
    const int MAX_SINMOV_SPEED = 50;
};

}