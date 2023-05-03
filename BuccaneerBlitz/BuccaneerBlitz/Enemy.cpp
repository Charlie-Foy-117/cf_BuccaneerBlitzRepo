#include "Enemy.h"
#include "LevelScreen.h"

Enemy::Enemy(LevelScreen* newLevelScreen)
	: SpriteObject()
	, lives()
	, spawnTime()
	, clock()
	, levelScreen(newLevelScreen)
{
	//srand(clock.getElapsedTime().asSeconds());
}

void Enemy::DropItem()
{
	int dropChance = rand() % 4;

	switch (dropChance)
	{
	case 0:
		levelScreen->SpawnPickUp(PickupType::LIFE, *this);
	case 1:
		//levelScreen->SpawnPickUp(PickupType::ANCHOR, *this);
		break;
	case 2:
		//levelScreen->SpawnPickUp(PickupType::MULTIFIRE, *this);
		break;
	case 3:
		//do nothing
		break;

	default:
		break;
	}
}
