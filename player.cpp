#include "player.h"

#include <iostream>

Player::Player(Rectangle body, std::string name, float speed)
{
    this->body = body;
    this->name = name;
    this->speed = speed;
    isJumping = false;
    jumpTimer = 0;
    isAlive = true;
    hp = 3;
}

Player::Player()
{
    isJumping = false;
    jumpTimer = 0;
    speed = 400.0f;
    isAlive = true;
    hp = 3;
}

Player::~Player()
{
    std::cout << "Player has been destroyed." << std::endl;
}

void Player::MoveRight()
{
    body.x += speed * GetFrameTime();
}

void Player::MoveLeft()
{
    body.x -= speed * GetFrameTime();
}

void Player::Jump()
{
    if (IsGrounded() && IsKeyPressed(KEY_SPACE))
    {
        isJumping = true;
        jumpTimer = jumpTime;
        body.y -= speed * GetFrameTime() * 1.5f;
    }

    if (IsKeyDown(KEY_SPACE) && isJumping)
    {
        if (jumpTimer > 0)
        {
            body.y -= speed * GetFrameTime() * 1.5f;
            jumpTimer -= GetFrameTime();
        }
        else
        {
            isJumping = false;
        }
    }
 
    if (IsKeyUp(KEY_SPACE))
    {
        isJumping = false;
    }
}

bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    // calculate the distance to intersection point
    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // if uA and uB are between 0-1, lines are colliding
    return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
}

bool Player::IsGrounded() const
{
    extern float florLevel;
    /*
    bool bot =  lineLine(0, florLevel,static_cast<float>(GetScreenWidth()),florLevel, body.x,body.y+body.height, body.x+body.width,body.y+body.height);
    bool left =   lineLine(0, florLevel,static_cast<float>(GetScreenWidth()),florLevel, body.x,body.y,body.x, body.y+body.height);
    bool right =  lineLine(0, florLevel,static_cast<float>(GetScreenWidth()),florLevel, body.x+body.width,body.y, body.x+body.width,body.y+body.height);
    bool top =    lineLine(0, florLevel,static_cast<float>(GetScreenWidth()),florLevel, body.x,body.y, body.x+body.width,body.y);
     return left || right || top || bot;
    */
    return static_cast<int>(florLevel) == static_cast<int>(body.y);
}

void Player::MoveDown()
{
    body.y += speed / 1.5f * GetFrameTime();
}

void Player::SetY(float y_)
{
    this->body.y = y_;
}

void Player::SetX(float x_)
{
    this->body.x = x_;
}

Rectangle Player::GetBody() const
{
    return body;
}

void Player::SetHp(int hpModifier)
{
    this->hp += hpModifier;
}

void Player::SetSpeed(float speed_)
{
    this->speed = speed_;
}

void Player::DrawPlayer() const
{
    DrawRectangleRec(GetBody(), BLACK);
}
