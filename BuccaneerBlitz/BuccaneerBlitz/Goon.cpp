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
	PhysicsObject::Update(frameTime);

	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		attackSound.play();
		levelScreen->SpawnProjectile(Projectile::GOONCANNONBALL, *this);
		cooldownTimer.restart();
	}
}

void Goon::HandleCollision(PhysicsObject& other)
{
	//checks if collision is player
	if (typeid(other).name() == typeid(Player).name())
	{
		ModifyLives(-1);
		other.ModifyLives(-1);
	}
	//checks if collision is cannonball
	else if (typeid(other).name() == typeid(CannonBall).name())
	{
		DropItem();
		ModifyLives(-1);
		other.ModifyLives(-1);
	}
	//if neither if statements return true then a new goon is spawned
	//this happens if goons spawns outside playing area
	else
	{
		levelScreen->SpawnEnemy(EnemyType::GOON);
	}
}

