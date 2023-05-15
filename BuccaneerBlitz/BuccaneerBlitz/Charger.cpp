#include "Charger.h"
#include "AssetManager.h"
#include "Player.h"

Charger::Charger(LevelScreen* newLevelScreen, Player* newPlayer)
	: Enemy(newLevelScreen)
	, acceleration()
	, velocity(0, 0)
    , speed(400.0f)
	, levelScreen(newLevelScreen)
	, player(newPlayer)
	, cooldownTimer()
	, cooldown(1.0f)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Charger_PNG.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setRotation(180);
    sprite.scale(0.5f, 0.5f);

    collisionScale = sf::Vector2f(0.4f, 0.9f);
	collisionOffset = sf::Vector2f(-65, -60);

    spawnTime = 7.0f;
}

void Charger::Update(sf::Time frameTime)
{
	//calculate direction to player
	sf::Vector2f directionToPlayer = sf::Vector2f(player->GetPosition().x + 100, player->GetPosition().y) - GetPosition();

	//distance
	float distance = std::sqrt(std::pow(directionToPlayer.x, 2) + std::pow(directionToPlayer.y, 2));
	//normalize direction vector
	sf::Vector2f unitDirection = directionToPlayer / distance;

	//set velocity to unit direction multiplied by speed
	sf::Vector2f velocity = unitDirection * speed;

	//apply movement code
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}

void Charger::HandleCollision(SpriteObject& other)
{
	if (typeid(other).name() == typeid(CannonBall).name())
	{
		DropItem();
	}
	ModifyLives(-1);
	other.ModifyLives(-1);
}

float Charger::GetSpawnTime()
{
	return spawnTime;
}
