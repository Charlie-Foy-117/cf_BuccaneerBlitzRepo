#include "Backplate.h"
#include "AssetManager.h"

Backplate::Backplate()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_Backplate_PNG.png"));
	sprite.setScale(2.4f, 2.4f);
}
