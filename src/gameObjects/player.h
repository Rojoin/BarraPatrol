﻿#pragma once
#include "raylib.h"
#include <string>

#include "Bullet.h"

class Player
{
private:

	bool deadState;
	bool jumpState;
	float gravity;
	float speed;
	Texture2D texture;
	bool IsGrounded() const;
	Rectangle body;

public:
	Player(Rectangle body, float speed);
	Player();
	~Player();
	void MoveRight();
	void MoveLeft();
	void jump();
	void update();
	void MoveDown();
	Bullet ShootUp() const;
	void draw();
	Rectangle getBody() const;

};
