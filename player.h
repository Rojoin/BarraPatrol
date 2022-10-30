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
    bool isGrounded;
    float jumpTime = 0.35f; 
    float jumpTimer; 
    float speed;
    Rectangle body{};
    std::string name;
};
