#include "SideBarrier.h"
#include "AssetManager.h"

SideBarrier::SideBarrier(sf::RenderWindow* newWindow)
	: SpriteObject()
	, window(newWindow)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level1SideBarrier_PNG.png"));
	ResetPosition("left");
	ResetPosition("right");

}

void SideBarrier::ResetPosition(std::string side)
{
	float xPos = window->getSize().x - sprite.getGlobalBounds().width;
	float yPos = window->getSize().y / 2.0f - sprite.getGlobalBounds().height / 2.0f;
	if (side == "left")
	{
		sprite.setScale(1.0f, 1.05f);
		collisionScale = sf::Vector2f(0.5f, 1.0f);
		collisionOffset = sf::Vector2f(60, 0);
		SetPosition(sf::Vector2f(0, 0));
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


