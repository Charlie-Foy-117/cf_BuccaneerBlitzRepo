#include "Pickups.h"

Pickups::Pickups()
	: PhysicsObject()
{
	velocity = sf::Vector2f(0, 400);
}

void Pickups::Update(sf::Time frameTime)
{
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}
