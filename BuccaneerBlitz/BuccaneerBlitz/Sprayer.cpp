#include "Sprayer.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Sprayer::Sprayer(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
	, acceleration()
	, velocity(0, 100)
	, cooldownTimer()
	, cooldown(0.5f)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Sprayer_PNG.png"));
	sprite.setScale(1.1f, 1.1f);
	collisionScale = sf::Vector2f(0.5f, 1.0f);
	spawnTime = 15.0f;
}

void Sprayer::Update(sf::Time frameTime)
{
	//moves sprayer down screen
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		levelScreen->SpawnProjectile(Projectile::SPRAYERCANNONBALL, *this);
		cooldownTimer.restart();
	}
}

void Sprayer::HandleCollision(SpriteObject& other)
{
	if (typeid(other).name() == typeid(Player).name())
	{
		ModifyLives(-1);
		other.ModifyLives(-1);
	}
	else if (typeid(other).name() == typeid(CannonBall).name())
	{
		DropItem();
		ModifyLives(-1);
		other.ModifyLives(-1);
	}
	else
	{
		levelScreen->SpawnEnemy(EnemyType::SPRAYER);
	}
}

float Sprayer::GetSpawnTime()
{
	return spawnTime;
}

sf::Vector2f Sprayer::GetVelocity()
{
	return velocity;
}
