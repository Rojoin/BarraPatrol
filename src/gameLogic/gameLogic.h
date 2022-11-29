#pragma once
#include "gameObjects/player.h"
#include"gameObjects/Obstacle.h"
#include "gameObjects/Enemy.h"
#include "gameObjects/Bullet.h"

using namespace OBJ;

bool isCharacterObstacleColliding(Player* character, Obstacle* obstacle);
bool isBulletEnemyColliding(Bullet* bullet, Enemy* enemy);