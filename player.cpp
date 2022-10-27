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
    speed;
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

void Player::MoveUp()
{
    body.y -= speed*GetFrameTime();
}

void Player::MoveDown()
{
    body.y += speed/2*GetFrameTime();
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
