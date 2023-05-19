#include "LifePickup.h"
#include "AssetManager.h"

LifePickup::LifePickup()
	: Pickups()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Pickups/cf_LifePickup_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
}

void LifePickup::HandleCollision(SpriteObject& other)
{
	SetAlive(false);
	if (other.GetAlive())
	{
		other.ModifyLives(1);
	}
}
