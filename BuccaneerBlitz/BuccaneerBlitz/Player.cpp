#include "Player.h"
#include "AssetManager.h"
#include "LevelScreen.h"

enum class PhysicsType
{
	VELOCITY_VERLET
};

Player::Player(sf::RenderWindow* newWindow, LevelScreen* newLevelScreen)
	: SpriteObject()
	, twoFramesOldPosition(0, 0)
	, velocity()
	, acceleration()
	, window(newWindow)
	, levelScreen(newLevelScreen)
	, cooldownTimer()
	, cooldown(1.0f)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Player/cf_Player1_PNG.png"));

	collisionScale = sf::Vector2f(0.45f, 0.95f);

	lives = 3;
}

void Player::Update(sf::Time frameTime)
{
	const float DRAG = 10.0f;
	const PhysicsType physics = PhysicsType::VELOCITY_VERLET;

	sf::Vector2f lastFramePos = GetPosition();

	switch (physics)
	{
	case PhysicsType::VELOCITY_VERLET:
	{
		//Velocity Verlet
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
		UpdateAcceleration();
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		//drag
		velocity.x = velocity.x - velocity.x * DRAG * frameTime.asSeconds();
		velocity.y = velocity.y - velocity.y * DRAG * frameTime.asSeconds();
	}
	break;

	default:
		//two frames ago (for next frame)
		twoFramesOldPosition = lastFramePos;
		break;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		FireCannonBall(cooldown);
	}
}

void Player::HandleCollision(SpriteObject& other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		//move in x direction
		newPosition.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		//move in y direction
		newPosition.y += depth.y;
		velocity.x = 0;
		acceleration.x = 0;
	}

	SetPosition(newPosition);
}

void Player::FireCannonBall(float newCooldown)
{
	if (cooldownTimer.getElapsedTime().asSeconds() > newCooldown)
	{
		//TODO: push back a copy of a cannon ball and make it
		levelScreen->SpawnProjectile(Projectile::CANNONBALL, *this);
		cooldownTimer.restart();
	}
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 10000;

	sf::Vector2f pos = sprite.getPosition();
	float spriteBottom = pos.y + sprite.getGlobalBounds().height;

	acceleration.x = 0;
	acceleration.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getPosition().y > 0)
	{
		acceleration.y = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && spriteBottom < window->getSize().y)
	{
		acceleration.y = ACCEL;
	}
}
