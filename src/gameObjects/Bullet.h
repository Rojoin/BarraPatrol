#pragma once
#include "raylib.h"

#include "system/Circle.h"

class Bullet
{
public:
    enum Shooter
    {
        player,
        helicopter,
        truck
    };
    Bullet(Shooter shooter, Vector2 direction, Vector2 position, float radius, float rotation, float speed);
    Bullet();
    ~Bullet();
    Vector2 GetPosition() const;
    Circle GetBody() const;
    void IsOutOfBounds();
    bool IsActive() const;
    void Move();
    void Draw(Texture2D texture) const;
    
private:
    bool isActive;
    Shooter shooter;
    Vector2 direction;
    float rotation;
    Circle body;
    float speed;
};
