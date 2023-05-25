#include "CannonBall.h"
#include "AssetManager.h"

CannonBall::CannonBall()
	: PhysicsObject()
	, collisionSound()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Player/cf_CannonBall_PNG.png"));
	SetSpriteScale(0.25f, 0.25f);
	collisionScale = sf::Vector2f(0.9f, 0.9f);

	SetEnumUsed(CollisionType::CIRCLE);

	collisionSound.setBuffer(AssetManager::RequestSoundBuffer("Assets/Sounds/501104__evretro__8-bit-damage-sound.wav"));

	velocity = sf::Vector2f(0, -400);
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

void CannonBall::HandleCollision(PhysicsObject& other)
{
	alive = false;
	if (typeid(other).name() != typeid(SideBarrier).name() && typeid(other).name() != typeid(BossRoomBarrier).name() && typeid(other).name() != typeid(Tentacle).name())
	{
		collisionSound.play();
		other.ModifyLives(-1);
	}
}
