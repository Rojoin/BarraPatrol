#pragma once
#include "raylib.h"
#include <string>

#include "Bullet.h"

class Player
{
private:
	Bullet* bullets[10];
	int bulletIndex;
	bool deadState;
	bool jumpState;
	float gravity;
	float speed;
	float scale;
	Texture2D texture;

public:
	Rectangle body;
	Player();
	~Player();
	void MoveRight();
	void MoveLeft();
	void jump();
	void update();
	bool isDead();
	void setDeadState(bool state);
	Rectangle getBody();
	Bullet ShootUp() const;
	void draw();
	Rectangle getBody() const;

};
