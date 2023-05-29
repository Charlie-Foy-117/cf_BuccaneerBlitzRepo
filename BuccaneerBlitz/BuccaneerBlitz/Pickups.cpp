#include "Pickups.h"

Pickups::Pickups()
	: PhysicsObject()
{
	velocity = sf::Vector2f(0, 400);
}

void Pickups::Update(sf::Time frameTime)
{
	PhysicsObject::Update(frameTime);
}
