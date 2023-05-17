#include "Overlay.h"
#include "AssetManager.h"

Overlay::Overlay()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_Overlay_PNG.png"));
	sprite.setScale(2.4f, 2.4f);
}
