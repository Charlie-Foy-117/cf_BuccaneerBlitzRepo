#include "TitleCard.h"
#include "AssetManager.h"

TitleCard::TitleCard()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_TitleCard_PNG.png"));
	sprite.setScale(2.4f, 2.4f);
	sprite.setRotation(10);
}
