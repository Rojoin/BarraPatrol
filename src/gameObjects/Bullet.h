#pragma once
#include "raylib.h"

#include "system/Circle.h"

class Bullet
{
public:

    Bullet();
    ~Bullet();
    Vector2 GetPosition() const;
    Circle GetBody() const;
    void IsOutOfBounds();
    bool IsActive() const;
    void Move();
    void draw() const;
    
private:
    Vector2 direction;
    Circle body;
    Texture2D texture;
    Sound sound;
    float rotation;
    bool isActive;
    float scale;
    float speed;


};
