#include "PirateBarricade.h"
#include "AssetManager.h"

PirateBarricade::PirateBarricade(LevelScreen* newLevelScreen)
	: Hazards()
	, acceleration()
	, velocity()
	, levelScreen(newLevelScreen)
	, cooldownTimer()
	, cooldown()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_PirateBarricade_PNG.png"));
}

void PirateBarricade::Update(sf::Time frameTime)
{
	//moves goon down screen
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}

void PirateBarricade::HandleCollision(SpriteObject& other)
{
}

float PirateBarricade::GetSpawnTime()
{
	return spawnTime;
}
