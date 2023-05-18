#include "Kraken.h"
#include "AssetManager.h"

Kraken::Kraken(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
	, velocity()
	, acceleration()
	, cooldownTimer()
	, cooldown()
	, levelScreen(newLevelScreen)
{
	//TODO: Create kraken sprite
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Kraken_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setRotation(180);

	lives = 15;
	bonusTime = 60.0f;
}

void Kraken::HandleCollision(SpriteObject& other)
{
}

void Kraken::Update(sf::Time frameTime)
{
}
