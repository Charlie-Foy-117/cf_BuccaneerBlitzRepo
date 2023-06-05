#include "PirateLord.h"
#include "AssetManager.h"
#include "Player.h"
#include "LevelScreen.h"

PirateLord::PirateLord(sf::RenderWindow* newWindow, LevelScreen* newLevelScreen, Player* newPlayer)
	: Enemy(newLevelScreen)
	, window(newWindow)
	, speed(500.0f)
	, tolerance(20.0f)
	, originalY()
	, xPositionMatched(false)
	, cooldownTimer()
	, cooldown(3)
	, levelScreen(newLevelScreen)
	, player(newPlayer)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_PirateLord_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setRotation(180);

	collisionScale = sf::Vector2f(0.4f, 0.9f);
	collisionOffset = sf::Vector2f(-128, -128);

	originalY = 300;
	lives = 10;
	bonusTime = 45.0f;
}

void PirateLord::HandleCollision(PhysicsObject& other)
{
	other.ModifyLives(-1);
	SetPosition(GetPosition().x, originalY);
	cooldownTimer.restart();
}

void PirateLord::Update(sf::Time frameTime)
{

	if (cooldownTimer.getElapsedTime().asSeconds() >= cooldown)
	{
		//checks if piratelord and player match x coords
		if (!xPositionMatched && std::abs(GetPosition().x - player->GetPosition().x) < tolerance)
		{
			xPositionMatched = true;

			//piratelord attacks
			attackSound.play();
		}

		//checks if x position is true
		if (xPositionMatched)
		{

			//moves down screen
			velocity = sf::Vector2f(0.0f, 1000.0f);

			PhysicsObject::Update(frameTime);

			//resets position to original y coord
			if (GetPosition().y >= window->getSize().y)
			{
				SetPosition(GetPosition().x, originalY);
				cooldownTimer.restart();
				xPositionMatched = false;
			}
		}
	}
	else
	{
		velocity = sf::Vector2f(0.0f, 0.0f);

		// Calculate direction to player
		sf::Vector2f directionToPlayer = sf::Vector2f(player->GetPosition().x, GetPosition().y) - GetPosition();

		// Distance
		float distance = std::sqrt(std::pow(directionToPlayer.x, 2.0f) + std::pow(directionToPlayer.y, 2.0f));
		// Normalize direction vector
		sf::Vector2f unitDirection;
		if (distance > 0)
		{
			unitDirection = directionToPlayer / distance;
		}
		else if (distance <= 0)
		{
			unitDirection = sf::Vector2f(0, 0);
		}

		// Set velocity to unit direction multiplied by speed
		velocity = unitDirection * speed;

		PhysicsObject::Update(frameTime);
	}
}
