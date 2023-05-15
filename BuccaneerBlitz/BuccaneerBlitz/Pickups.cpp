#include "Pickups.h"

Pickups::Pickups()
	: SpriteObject()
	, velocity(0, 400)
	, acceleration()
{
}

void Pickups::Update(sf::Time frameTime)
{
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}
