#include "gameLogic.h"

#include "gameObjects/Enemy.h"
#include "system/collisionFunctions.h"
#include "gameObjects/player.h"

bool isCharacterObstacleColliding(Player* character, Obstacle* obstacle)
{
	if (isRecRecColliding(character->getBody(),obstacle->getRec()))
	{
		return true;
	}
	return false;
}
bool isBulletEnemyColliding(Bullet* bullet, Enemy* enemy)
{
	if (isCircleRecColliding(bullet->getBody(),enemy->getBody()))
	{
		return true;
	}
	return false;
}


