#include "Goon.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Goon::Goon(LevelScreen* newLevelScreen)
	: Enemy()
	, velocity(0, 200)
	, acceleration()
	, levelScreen(newLevelScreen)
	, cooldownTimer()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Goon_PNG.png"));
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setRotation(180);
	collisionScale = sf::Vector2f(0.45f, 0.95f);
	collisionOffset = sf::Vector2f(-128, -128);

	spawnTime = 3.5f;
}

void Goon::Update(sf::Time frameTime)
{
	//moves goon down screen
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

	//calls every frame to check is goon can be spawned
	SpawnGoon();
}

void Goon::HandleCollision(SpriteObject& other)
{
}

float Goon::GetSpawnTime()
{
	return spawnTime;
}

void Goon::SpawnGoon()
{
	//spawns goon is elapsed time is more than 3
	if (cooldownTimer.getElapsedTime().asSeconds() > spawnTime)
	{
		levelScreen->SpawnEnemy(GOON);
		cooldownTimer.restart();
	}
}

