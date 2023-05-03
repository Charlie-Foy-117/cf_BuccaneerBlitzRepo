#include "LifePickup.h"
#include "AssetManager.h"

LifePickup::LifePickup()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Pickups/cf_LifePickup_PNG.png"));
}

void LifePickup::HandleCollision(SpriteObject& other)
{
	SetAlive(false);
	other.GainLife();
}
