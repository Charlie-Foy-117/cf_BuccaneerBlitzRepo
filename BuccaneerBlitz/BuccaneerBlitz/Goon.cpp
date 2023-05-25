#include "Goon.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Goon::Goon(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
	, levelScreen(newLevelScreen)
	, cooldownTimer()
	, cooldown(2.5f)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Goon_PNG.png"));
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setRotation(180);
	collisionScale = sf::Vector2f(0.45f, 0.95f);
	collisionOffset = sf::Vector2f(-128, -128);

	spawnTime = 2.0f;
	velocity = sf::Vector2f(0, 200);
}

void Goon::Update(sf::Time frameTime)
{
	//moves goon down screen
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		attackSound.play();
		levelScreen->SpawnProjectile(Projectile::GOONCANNONBALL, *this);
		cooldownTimer.restart();
	}
}

void Goon::HandleCollision(PhysicsObject& other)
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
		levelScreen->SpawnEnemy(EnemyType::GOON);
	}
}

