#include "player.h"
#include "raylib.h"
#include <iostream>

#include "Bullet.h"
#include "system/draw.h"

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

    Rectangle source{ 0,0,(float)texture.width,(float)texture.height };
    Rectangle dest{ body.x  ,body.y,(float)texture.width * scale / 2,(float)texture.height * scale / 2 };
    drawTexture(texture, source, dest, { static_cast<float>(texture.width) / 2.0f,static_cast<float>(texture.height) / 2.0f }, 0, scale / 2, WHITE);
}

Bullet Player::ShootUp() const
{
    const float size = body.width*1.3f;
    const float bulletSpeed = speed * 1.f;
    return Bullet();
}

