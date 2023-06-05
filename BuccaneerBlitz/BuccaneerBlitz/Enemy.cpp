#include "Enemy.h"
#include "LevelScreen.h"
#include "AssetManager.h"
#include <random>

Enemy::Enemy(LevelScreen* newLevelScreen)
	: PhysicsObject()
	, spawnTime()
	, clock()
	, levelScreen(newLevelScreen)
	, bonusTime(0)
	, attackSound()
{
	attackSound.setBuffer(AssetManager::RequestSoundBuffer("Assets/Sounds/522209__kutejnikov__explosion.wav"));
	attackSound.setVolume(10.0f);
}

void Enemy::DropItem()
{
	//seed the random number generator
	std::random_device rd;

	//use uniform_int_distribution object to generate numbers in the range 0-3
	std::uniform_int_distribution<int> dist(0, 3);

	int dropChance = dist(rd);

	//randomly chooses on of 4 cases to run
	switch (dropChance)
	{
	case 0:
		//spawns anchor
		levelScreen->SpawnPickUp(PickupType::ANCHOR, GetPosition());
		break;
	case 1:
		//spawns life
		levelScreen->SpawnPickUp(PickupType::LIFE, GetPosition());
		break;
	case 2:
		//spawns multifire
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
	//increases level by 1
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
