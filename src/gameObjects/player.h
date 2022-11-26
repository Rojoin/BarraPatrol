#pragma once
#include <raylib.h>
#include <string>

#include "Bullet.h"

class Player
{
public:
    Player(Rectangle body, std::string name, float speed);
    Player();
    ~Player();
    void MoveRight();
    void MoveLeft();
    void Jump();
    void MoveDown();
    Bullet ShootUp() const;
    Bullet ShootRight() const;
    void Draw(Texture2D playerTexture) const;
    Rectangle GetBody() const;
    void SetY(float y_);
    void SetX(float x_);
    void SetHp(int hpModifier);
    void SetSpeed(float speed_);
private:
    int hp;
    bool isAlive;
    bool isJumping;
    float jumpTime = 0.18f; 
    float jumpTimer; 
    float speed;
    bool IsGrounded() const;
    Rectangle body{};
    std::string name;
};
