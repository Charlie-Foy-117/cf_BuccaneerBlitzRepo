#include "Sprayer.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Sprayer::Sprayer(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
	, cooldownTimer()
	, cooldown(0.5f)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Sprayer_PNG.png"));
	sprite.setScale(1.1f, 1.1f);
	collisionScale = sf::Vector2f(0.5f, 1.0f);
	spawnTime = 15.0f;
	velocity = sf::Vector2f(0, 100);
}

void Sprayer::Update(sf::Time frameTime)
{
	//moves sprayer down screen
	PhysicsObject::Update(frameTime);

	//spawns projectile whenever timer is larger than cooldown
	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		if (alive)
		{
			attackSound.play();
		}
		//spawns cannonballs
		levelScreen->SpawnProjectile(Projectile::SPRAYERCANNONBALL, *this);
		//restarts timer
		cooldownTimer.restart();
	}
}

void Sprayer::HandleCollision(PhysicsObject& other)
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
		//if instance spawns outside playing area it spawns another
		ModifyLives(-1);
		levelScreen->SpawnEnemy(EnemyType::SPRAYER);
	}
}

sf::Vector2f Sprayer::GetVelocity()
{
	return velocity;
}
