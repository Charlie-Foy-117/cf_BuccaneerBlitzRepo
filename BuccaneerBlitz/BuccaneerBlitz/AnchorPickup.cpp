#include "AnchorPickup.h"
#include "AssetManager.h"
#include "Player.h"

AnchorPickup::AnchorPickup()
	: Pickups()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Pickups/cf_AnchorPickup_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
}

void AnchorPickup::HandleCollision(PhysicsObject& other)
{
	SetAlive(false);
}
