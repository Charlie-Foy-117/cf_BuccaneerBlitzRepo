#include "Kraken.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Kraken::Kraken(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
	, velocity(200, 0)
	, acceleration()
	, cooldownTimer()
	, cooldown(3.0f)
	, levelScreen(newLevelScreen)
{
	//TODO: Create kraken sprite
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Kraken_PNG.png"));
	sprite.setScale(0.75f, 0.75f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);

	collisionScale = sf::Vector2f(0.45f, 0.7f);
	collisionOffset = sf::Vector2f(-190, -200);

	lives = 15;
	bonusTime = 60.0f;
}

void Kraken::HandleCollision(SpriteObject& other)
{
	if (typeid(other).name() == typeid(SideBarrier).name())
	{
		velocity = -velocity;
	}
}

void Kraken::Update(sf::Time frameTime)
{
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		levelScreen->SpawnProjectile(Projectile::KRAKENTENTACLES, *this);
		cooldownTimer.restart();
	}
}
