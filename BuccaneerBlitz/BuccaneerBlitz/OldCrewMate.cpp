#include "OldCrewMate.h"
#include "AssetManager.h"
#include "SideBarrier.h"
#include "LevelScreen.h"

OldCrewMate::OldCrewMate(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
    , velocity(200, 0)
    , acceleration()
	, cooldownTimer()
	, cooldown(1.0f)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_OldCrewMate_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setRotation(180);

	collisionScale = sf::Vector2f(0.5f, 1.0f);
	collisionOffset = sf::Vector2f(-128, -128);
    
	lives = 5;
	bonusTime = 30.0f;
}

void OldCrewMate::HandleCollision(SpriteObject& other)
{
	if (typeid(other).name() == typeid(SideBarrier).name())
	{
		velocity = -velocity;
	}
}

void OldCrewMate::Update(sf::Time frameTime)
{
    sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
    SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
    velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f; 

	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		levelScreen->SpawnProjectile(Projectile::OLDCREWMATECANNONBALLS, *this);
		cooldownTimer.restart();
	}
}
