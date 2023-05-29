#include "Kraken.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Kraken::Kraken(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
	, cooldownTimer()
	, cooldown(3.0f)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Kraken_PNG.png"));
	sprite.setScale(0.75f, 0.75f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);

	collisionScale = sf::Vector2f(0.45f, 0.7f);
	collisionOffset = sf::Vector2f(-190, -200);

	lives = 15;
	bonusTime = 60.0f;
	velocity = sf::Vector2f(200, 0);
}

void Kraken::HandleCollision(PhysicsObject& other)
{
	//if collision is side barrier changes x direction
	if (typeid(other).name() == typeid(SideBarrier).name())
	{
		velocity = -velocity;
	}
	//if player collides with kraken player loses life
	if (typeid(other).name() == typeid(Player).name())
	{
		other.ModifyLives(-1);
	}
}

void Kraken::Update(sf::Time frameTime)
{
	PhysicsObject::Update(frameTime);

	//only spawns projectile if timer is larger than the cooldown since last spawned
	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		attackSound.play();
		levelScreen->SpawnProjectile(Projectile::KRAKENTENTACLES, *this);
		cooldownTimer.restart();
	}
}
