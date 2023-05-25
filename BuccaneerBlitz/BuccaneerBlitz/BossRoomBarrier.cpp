#include "BossRoomBarrier.h"
#include "AssetManager.h"

BossRoomBarrier::BossRoomBarrier(sf::RenderWindow* newWindow, int* newLevelNumber)
	: PhysicsObject()
	, levelNumber(newLevelNumber)
	, window(newWindow)
{
	UpdateSpriteAsset(*levelNumber);
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_BossRoom1Barrier_PNG.png"));
	sprite.setScale(2.4f, 2.4f);

	collisionScale = sf::Vector2f(1.0f, 0.1f);
	collisionOffset = sf::Vector2f(0, -500);
}

void BossRoomBarrier::HandleCollision(PhysicsObject& other)
{
	PhysicsObject::HandleCollision(other);
}

void BossRoomBarrier::UpdateSpriteAsset(int newLevelNumber)
{
	//checks what input equals to change boss room to desired sprite for level
	if (newLevelNumber == 2)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_BossRoom1Barrier_PNG.png"));
	}
	else if (newLevelNumber == 4)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_BossRoom2Barrier_PNG.png"));
	}
	else if (newLevelNumber == 6)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_BossRoom3Barrier_PNG.png"));
	}
	else
	{
		//error...
	}
}
