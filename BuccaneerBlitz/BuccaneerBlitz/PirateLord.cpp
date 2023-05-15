#include "PirateLord.h"
#include "AssetManager.h"
#include "Player.h"

PirateLord::PirateLord(LevelScreen* newLevelScreen, Player* newPlayer)
	: Enemy(newLevelScreen)
	, velocity()
	, acceleration()
	, speed(500.0f)
	, cooldownTimer()
	, cooldown(10)
	, levelScreen(newLevelScreen)
	, player(newPlayer)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_PirateLord_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setRotation(180);

	collisionScale = sf::Vector2f(0.4f, 0.9f);
	collisionOffset = sf::Vector2f(-128, -128);

	lives = 10;
}

void PirateLord::HandleCollision(SpriteObject& other)
{
}

void PirateLord::Update(sf::Time frameTime)
{
	if (cooldownTimer.getElapsedTime().asSeconds() >= cooldown && GetPosition().x == player->GetPosition().x)
	{
		velocity = sf::Vector2f(0.0f, 1000.0f);

		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
	}
	else
	{
		velocity = sf::Vector2f(0.0f, 0.0f);

		//calculate direction to player
		sf::Vector2f directionToPlayer = sf::Vector2f(player->GetPosition().x, GetPosition().y) - GetPosition();

		//distance
		float distance = std::sqrt(std::pow(directionToPlayer.x, 2) + std::pow(directionToPlayer.y, 2));
		//normalize direction vector
		sf::Vector2f unitDirection;
		if (distance > 0)
		{
			unitDirection = directionToPlayer / distance;
		}
		else
		{
			unitDirection = sf::Vector2f(0, 0);
		}

		//set velocity to unit direction multiplied by speed
		sf::Vector2f velocity = unitDirection * speed;

		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
	}
}
