#include "LifeUI.h"
#include "AssetManager.h"

LifeUI::LifeUI()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_LifeUI_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
}
