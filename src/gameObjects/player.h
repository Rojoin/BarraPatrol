#pragma once
#include "raylib.h"
#include <string>

#include "Bullet.h"

class Player
{
private:

	Bullet* bullet;
	bool deadState;
	bool jumpState;
	float gravity;
	float speed;
	Rectangle body;
	float scale;
	Texture2D texture;



public:
	Player();
	~Player();
	Rectangle getBody();
	void moveRight();
	void moveLeft();
	void jump();
	void update();
	bool isDead();
	void setDeadState(bool state);
	Bullet* getBullet();
	void updateBullet();
	void drawBullet();
	void draw();
	void ShootUp();


};
