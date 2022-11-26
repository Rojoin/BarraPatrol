#pragma once
#include "raylib.h"

#include "system/Circle.h"

class Bullet
{
public:

    Bullet();
    ~Bullet();
    Vector2 getPosition() const;
    Circle getBody() const;
    void isOutOfBounds();
    bool isActive() const;
    void move();
    void draw() const;
    
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
