#include "MultiFirePickup.h"
#include "AssetManager.h"

MultiFirePickup::MultiFirePickup()
	: Pickups()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Pickups/cf_MultiFirePickup_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
}

void MultiFirePickup::HandleCollision(PhysicsObject& other)
{
	SetAlive(false);
}
