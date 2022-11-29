#pragma once
#include "raylib.h"

#include "system/Circle.h"

class Bullet
{
public:

    Bullet(float x, float y);
    ~Bullet();
    Vector2 getPosition();
    Circle getBody();
    bool isActive() ;
    void move();
    void draw();
    void setActiveState(bool state);
    void setDirection(Vector2 dir);
    void setPosition(float x, float y);
private:
    Vector2 direction;
    Circle body;
    Texture2D texture;
    Sound sound;
    float rotation;
    bool activeState;
    float scale;
    float speed;
    const float MAX_SPEED_FORCE = 500.0f;
    const float MAX_CIRCLE_RADIUS = 10;

};
