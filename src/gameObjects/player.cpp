#include "player.h"
#include "raylib.h"
#include <iostream>

#include "Bullet.h"

Player::Player(Rectangle body, float speed)
{
    this->body = body;
    this->speed = speed;
    jumpState = false;
    deadState = true;
    gravity = 200.0f;
}

Player::Player()
{
    jumpState = false;
    speed = 400.0f;
    deadState = true;

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

void Player::jump()
{
    jumpState = true;
}

void Player::update()
{
    static float jumpTimer = 0.8f;

    if (jumpState)
    {
        jumpTimer -= GetFrameTime();
        body.y += GetFrameTime() * -gravity;
        if (jumpTimer <= 0)
        {
            jumpState = false;
            jumpTimer = 0.8f;
        }
    }
    else if (body.y <= 600.0f)
    {
        body.y += GetFrameTime() * gravity;
    }
    else if (body.y > 600.0f)
    {
        body.y = 600.0f;
    }
}


Rectangle Player::getBody() const
{
    return body;
}


void Player::draw()
{
    const Rectangle carRec = {0,0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    DrawTextureRec(texture, carRec, {body.x, body.y-texture.height/2}, RAYWHITE);
    //DrawRectangleRec(body, BLACK);
}

Bullet Player::ShootUp() const
{
    const float size = body.width*1.3f;
    const float bulletSpeed = speed * 1.f;
    return Bullet();
}

