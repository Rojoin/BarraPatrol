#pragma once
#include <raylib.h>
#include <string>

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
    void SetY(float y_);
    void SetX(float x_);
    Rectangle GetBody() const;
    void SetHp(int hpModifier);
    void SetSpeed(float speed_);
    void DrawPlayer() const;
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
