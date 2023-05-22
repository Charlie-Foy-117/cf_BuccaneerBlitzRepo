#include "Enemy.h"
#include "LevelScreen.h"
#include <random>

Enemy::Enemy(LevelScreen* newLevelScreen)
	: SpriteObject()
	, spawnTime()
	, clock()
	, levelScreen(newLevelScreen)
	, bonusTime(0)
{

}

void Enemy::DropItem()
{
	//seed the random number generator
	std::random_device rd;

	//use uniform_int_distribution object to generate numbers in the range 0-3
	std::uniform_int_distribution<int> dist(0, 3);

	int dropChance = dist(rd);

	switch (dropChance)
	{
	case 0:
		levelScreen->SpawnPickUp(PickupType::ANCHOR, GetPosition());
		break;
	case 1:
		levelScreen->SpawnPickUp(PickupType::LIFE, GetPosition());
		break;
	case 2:
		levelScreen->SpawnPickUp(PickupType::MULTIFIRE, GetPosition());
		break;
	case 3:
		//do nothing
		break;

	default:
		break;
	}
}

void Enemy::KillBoss()
{
	levelScreen->levelStageNumber++;
}

float Enemy::GetBonusTime()
{
	return bonusTime;
}

float Enemy::GetSpawnTime()
{
	return spawnTime;
}
