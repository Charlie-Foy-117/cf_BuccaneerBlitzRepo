#include "AnchorUI.h"
#include "AssetManager.h"

AnchorUI::AnchorUI()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_AnchorUI_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
}

void AnchorUI::SetOpacity(bool hasAnchor)
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
