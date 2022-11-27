#include "gameLogic.h"
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
