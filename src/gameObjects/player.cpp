#include "player.h"
#if _DEBUG
#include <iostream>
#endif 

#include "raylib.h"
#include "Bullet.h"
#include "system/draw.h"

Texture2D playerTexture;
Sound playerSound;

Player::Player()
{
    this->body = { 200.0f,600.0f,50,50 };
    this->texture = playerTexture;
    this->speed = MAX_SPEED_FORCE;
    this->score = 0;
    this->scale = 0.10f;
    this->animIndex = 0;
    this->animTimer = 1.0f;
    this->sound = playerSound;
    jumpState = false;
    deadState = false;
    gravity = MAX_GRAVITY_FORCE;
    bullet =  new Bullet(body.x,body.y);
	
}

Player::~Player()
{
    std::cout << "Player has been destroyed." << std::endl;
    delete bullet;
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
	if (body.y >= 600.0f)
	{
    jumpState = true;
    PlaySound(sound);
		
	}
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

    animTimer -= GetFrameTime();
    if (animTimer <= 0)
    {
        animIndex++;
        if (animIndex > 1.0f)
        {
            animIndex = 0;
        }
        animTimer = 1.0f;
    }
    std::cout << animIndex;
   
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
        bullet->setPosition(body.x+texture.width/8*scale, body.y);
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
    float textureWidth = static_cast<float>(texture.width) / 2.0f;
    

    Rectangle source{ textureWidth*animIndex,0,textureWidth,(float)texture.height};
    Rectangle dest{ body.x+ textureWidth * scale / 4   ,body.y+ texture.height/2 * scale / 4,(float)texture.width/2 * scale/2 ,(float)texture.height *scale/2};

#if _DEBUG

    DrawRectangleRec(body, RED);
#endif

    drawTexture(texture, source, dest, { static_cast<float>(texture.width) /4.0f,static_cast<float>(texture.height) / 2.0f }, 0, scale/2, WHITE);
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



