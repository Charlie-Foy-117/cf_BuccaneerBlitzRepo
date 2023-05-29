#include "Buoy.h"
#include "AssetManager.h"

Buoy::Buoy()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_Buoy_PNG.png"));
	sprite.setScale(1.0f, 1.0f);
}
