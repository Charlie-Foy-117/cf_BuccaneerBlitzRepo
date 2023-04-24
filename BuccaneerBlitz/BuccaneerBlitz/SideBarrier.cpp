#include "SideBarrier.h"
#include "AssetManager.h"

SideBarrier::SideBarrier(sf::RenderWindow* newWindow, int* newLevelNumber)
	: SpriteObject()
	, levelNumber(newLevelNumber)
	, window(newWindow)
{
	UpdateSpriteAsset(*levelNumber);
	ResetPosition("left");
	ResetPosition("right");

}

void SideBarrier::ResetPosition(std::string side)
{
	float xPos = window->getSize().x - sprite.getGlobalBounds().width;
	float yPos = window->getSize().y / 2.0f - sprite.getGlobalBounds().height / 2.0f;
	if (side == "left")
	{
		SetPosition(sf::Vector2f(0, 0));
		sprite.setScale(1.0f, 1.05f);
		collisionScale = sf::Vector2f(0.5f, 1.0f);
		collisionOffset = sf::Vector2f(-65, 0);
	}
	if (side == "right")
	{
		sprite.setScale(1.0f, 1.05f);
		collisionScale = sf::Vector2f(0.5f, 1.0f);
		collisionOffset = sf::Vector2f(60, 0);
		SetPosition(sf::Vector2f(xPos, 0));
	}
	else
	{
		SetPosition(0, 0);
	}

}

void SideBarrier::HandleCollision(SpriteObject& other)
{
	SpriteObject::HandleCollision(other);
}

void SideBarrier::UpdateSpriteAsset(int newLevelNumber)
{
	switch (newLevelNumber)
	{
	case 1:
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level1SideBarrier_PNG.png"));
		break;

	case 2:
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level2SideBarrier_PNG.png"));
		break;

	case 3:
		//sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level3SideBarrier_PNG.png"));
		break;

	default:
		break;
	}
}


