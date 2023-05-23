#include "Tentacle.h"
#include "AssetManager.h"

Tentacle::Tentacle(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
	, velocity(200, 0)
	, acceleration()
	, levelScreen(newLevelScreen)
	, flipX(false)

{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_KrakenTentacle_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);

	collisionScale = sf::Vector2f(0.6f, 1.0f);
	collisionOffset = sf::Vector2f(-128, -135);

	spawnTime = 2.5f;
	lives = 4;
}

void Tentacle::HandleCollision(SpriteObject& other)
{
	if (typeid(other).name() == typeid(SideBarrier).name())
	{
		ModifyLives(-1);
		velocity = -velocity;
		SetPosition(GetPosition().x, GetPosition().y + 40);
		if (!flipX)
		{
			flipX = true;
			return;
		}
		if (flipX)
		{
			flipX = false;
			return;
		}
	}
	else
	{
		alive = false;
		other.ModifyLives(-1);
	}
}

void Tentacle::Update(sf::Time frameTime)
{
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

	if (!flipX)
	{
		sprite.setScale(0.5f, 0.5f);
	}
	if (flipX)
	{
		sprite.setScale(-0.5f, 0.5f);
	}
}

void Tentacle::SetVelocity(float newX, float newY)
{
	velocity.x = newX;
	velocity.y = newY;
}
