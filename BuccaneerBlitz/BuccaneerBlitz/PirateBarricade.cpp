#include "PirateBarricade.h"
#include "AssetManager.h"

PirateBarricade::PirateBarricade(LevelScreen* newLevelScreen)
	: Hazards()
	, acceleration(0, 40)
	, velocity()
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_PirateBarricade_PNG.png"));
	sprite.setScale(1.5f, 1.5f);
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
}

float PirateBarricade::GetSpawnTime()
{
	return spawnTime;
}
