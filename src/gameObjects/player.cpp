#include "player.h"
#include "raylib.h"
#include <iostream>

#include "Bullet.h"

Player::Player(Rectangle body, float speed)
{
    this->body = body;
    this->speed = speed;
    jumpState = false;
    jumpTimer = 0;
    deadState = true;
    gravity = 200.0f;
}

Player::Player()
{
    jumpState = false;
    jumpTimer = 0;
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

