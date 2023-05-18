#include "PirateBarricade.h"
#include "AssetManager.h"

PirateBarricade::PirateBarricade(LevelScreen* newLevelScreen, int* newLevelNumber)
	: Hazards()
	, acceleration()
	, velocity(0, 60)
	, levelScreen(newLevelScreen)
	, levelNumber(newLevelNumber)
{
	UpdateSpriteAsset(*levelNumber);
	sprite.setScale(1.5f, 1.5f);
	collisionScale = sf::Vector2f(1.0f, 0.6f);
	spawnTime = 30.0f;
}

void PirateBarricade::Update(sf::Time frameTime)
{
	//moves barricade down screen
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}

void PirateBarricade::HandleCollision(SpriteObject& other)
{
	if (typeid(other).name() == typeid(Anchor).name() || typeid(other).name() == typeid(Player).name())
	{
		ModifyLives(-1);
	}
	other.ModifyLives(-1);
}

float PirateBarricade::GetSpawnTime()
{
	return spawnTime;
}

void PirateBarricade::UpdateSpriteAsset(int newLevelNumber)
{
	//checks what input equals to change side barrier to desired look for level
	if (newLevelNumber == 1 || newLevelNumber == 2)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_PirateBarricade_PNG.png"));
	}
	else if (newLevelNumber == 3 || newLevelNumber == 4)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_PirateBarricade2_PNG.png"));
	}
	else if (newLevelNumber == 5 || newLevelNumber == 6)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_PirateBarricade3_PNG.png"));
	}
	else
	{
		//error...
	}
}
