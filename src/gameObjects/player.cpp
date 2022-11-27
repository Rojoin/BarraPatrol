#include "player.h"
#include "raylib.h"
#include <iostream>

#include "Bullet.h"
#include "system/draw.h"

Texture2D bodyTexture;


Player::Player()
{
    this->body = { 200.0f,600.0f,50,50 };
    this->texture = bodyTexture;
    this->speed = 400;
    this->score = 0;
    jumpState = false;
    deadState = false;
    gravity = 200.0f;
 bullet =  new Bullet(body.x,body.y);
	
}

Player::~Player()
{
    std::cout << "Player has been destroyed." << std::endl;
}

void Player::moveRight()
{
    body.x += speed * GetFrameTime();
}

void Player::moveLeft()
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

bool Player::isDead()
{
    return deadState;
}

void Player::setDeadState(bool state)
{
    this->deadState = state;
}

void Player::updateBullet()
{
    
    if (bullet->isActive())
    {
        bullet->move();
        if (bullet->getPosition().y <= 0-bullet->getBody().radius)
        {
            bullet->setActiveState(false);
        }
	}
    else
    {
        bullet->setPosition(body.x, body.y);
    }
}

void Player::drawBullet()
{
    
	    if (bullet->isActive())
	    {
        bullet->draw();
	    }
    
}

Rectangle Player::getBody()
{
    return this->body;
}

Bullet* Player::getBullet()
{
    return bullet;
}




void Player::draw()
{
    Rectangle source{ 0,0,(float)texture.width,(float)texture.height};
    Rectangle dest{ body.x  ,body.y,(float)texture.width * scale / 2,(float)texture.height * scale / 2 };
#if _DEBUG
    DrawRectangleRec(body, RED);
#endif
    drawTexture(texture, source, dest, { static_cast<float>(texture.width) / 2.0f,static_cast<float>(texture.height) / 2.0f }, 0, scale / 2, WHITE);
}

void Player::ShootUp() 
{
    if (!bullet->isActive())
    {
        bullet->setDirection({ 0,-1 });
        bullet->setActiveState(true);
    }
}

void Player::scoreUp(float point)
{
    score += point;
}

float Player::getScore()
{
    return score;
}



