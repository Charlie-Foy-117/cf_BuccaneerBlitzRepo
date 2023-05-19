#include "MultiFireUI.h"
#include "AssetManager.h"

MultiFireUI::MultiFireUI()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_MultiFireUI_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
}

void MultiFireUI::SetOpacity(bool hasAnchor)
{
	if (hasAnchor)
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 51));
	}
}
