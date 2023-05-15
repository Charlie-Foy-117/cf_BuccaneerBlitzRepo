#include "CannonBall.h"
#include "AssetManager.h"

CannonBall::CannonBall()
	: SpriteObject()
	, acceleration()
	, velocity(sf::Vector2f(0, -400))
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Player/cf_CannonBall_PNG.png"));
	SetSpriteScale(0.25f, 0.25f);
	collisionScale = sf::Vector2f(0.9f, 0.9f);

	SetEnumUsed(CollisionType::CIRCLE);
}

void CannonBall::Update(sf::Time frameTime)
{
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}

void CannonBall::SetVelocity(float newX, float newY)
{
	velocity.x = newX;
	velocity.y = newY;
}

sf::Vector2f CannonBall::GetVelocity()
{
	return velocity;
}

void CannonBall::HandleCollision(SpriteObject& other)
{
	alive = false;
	if (typeid(other).name() != typeid(SideBarrier).name() && typeid(other).name() != typeid(BossRoomBarrier).name())
	{
		other.ModifyLives(-1);
	}
}
