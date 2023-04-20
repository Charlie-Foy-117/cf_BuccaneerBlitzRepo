#include "CannonBall.h"
#include "AssetManager.h"

CannonBall::CannonBall()
	: SpriteObject()
	, acceleration()
	, velocity(sf::Vector2f(0, -200))
	, width(sprite.getGlobalBounds().width)
	, height(sprite.getGlobalBounds().height)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Player/cf_CannonBall_PNG.png"));
	sprite.setScale(0.25f, 0.25f);
	collisionScale = sf::Vector2f(0.9f, 0.9f);

	SetEnumUsed(CollisionType::CIRCLE);
}

void CannonBall::Update(sf::Time frameTime)
{
	//Velocity Verlet
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}

void CannonBall::HandleCollision(SpriteObject& other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
}

float CannonBall::GetWidth()
{
	return width;
}

float CannonBall::GetHeight()
{
	return height;
}
