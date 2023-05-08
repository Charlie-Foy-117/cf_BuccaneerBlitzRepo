#include "PirateBarricade.h"
#include "AssetManager.h"

PirateBarricade::PirateBarricade(LevelScreen* newLevelScreen)
	: Hazards()
	, acceleration()
	, velocity(0, 60)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_PirateBarricade_PNG.png"));
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
