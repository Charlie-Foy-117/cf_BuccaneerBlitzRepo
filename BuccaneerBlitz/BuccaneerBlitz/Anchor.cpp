#include "Anchor.h"
#include "AssetManager.h"

Anchor::Anchor()
	: PhysicsObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_AnchorUI_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
	sprite.setRotation(180);
	collisionScale = sf::Vector2f(0.65f, 0.2f);
	collisionOffset = sf::Vector2f(-128, -170);

	velocity = sf::Vector2f(0, -400);
}

void Anchor::Update(sf::Time frameTime)
{
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}

void Anchor::SetVelocity(float newX, float newY)
{
	velocity.x = newX;
	velocity.y = newY;
}

void Anchor::HandleCollision(PhysicsObject& other)
{
	alive = false;
	other.ModifyLives(-1);
}
