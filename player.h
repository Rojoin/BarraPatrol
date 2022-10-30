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
    void MoveUp();
    void MoveDown();
    void SetY(float y_);
    Rectangle GetBody() const;
    void SetHp(int hpModifier);
    void SetSpeed(float speed_);
    void DrawPlayer() const;
private:
    int hp;
    bool isAlive;
    bool isJumping;
    float jumpTime = 0.14f; 
    float jumpTimer; 
    float speed;
    bool IsGrounded();
    Rectangle body{};
    std::string name;
};
