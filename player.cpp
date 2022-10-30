#include "player.h"

#include <iostream>

Player::Player(Rectangle body, std::string name, float speed)
{
    this->body = body;
    this->name = name;
    this->speed = speed;
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

//SetX, SetY
//ModifyX(float xModifier), ModifyY(float yModifier)
//or MoveLeft, MoveRight, MoveUp
void Player::MoveRight()
{
    body.x += speed * GetFrameTime();
}

void Player::MoveLeft()
{
    body.x -= speed*GetFrameTime();
}

void Player::MoveUp() //BUSCAR MEJOR IMPLEMENTACION DE SALTO
{
    if(IsGrounded() && IsKeyPressed(KEY_SPACE))
    {
        isJumping = true;
        jumpTimer = jumpTime;
    }
    if(IsKeyDown(KEY_SPACE))
    {
        if (jumpTimer > 0)
        {        
            
            body.y -= speed*GetFrameTime()*1.5f;
            jumpTimer -= GetFrameTime();
        }
    }
    if (IsKeyReleased(KEY_SPACE))
    {
        isJumping = false;
    }
}
bool Player::IsGrounded()
{
    extern float florLevel;
    return static_cast<int>(florLevel) == static_cast<int>(body.y);
}

void Player::MoveDown()
{
    body.y += speed/1.5f*GetFrameTime();
}

void Player::SetY(float y_)
{
    this->body.y = y_;
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
    DrawRectangleRec(GetBody(), WHITE);
}
