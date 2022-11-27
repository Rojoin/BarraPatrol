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
    void isOutOfBounds();
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


};
