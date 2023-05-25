#include "SideBarrier.h"
#include "AssetManager.h"

SideBarrier::SideBarrier(sf::RenderWindow* newWindow, int* newLevelNumber)
	: PhysicsObject()
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
	}
	if (side == "right")
	{
		sprite.setScale(1.0f, 1.05f);
		SetPosition(sf::Vector2f(xPos, 0));
	}
	else
	{
		SetPosition(0, 0);
	}

}

void SideBarrier::HandleCollision(PhysicsObject& other)
{
	PhysicsObject::HandleCollision(other);
}

void SideBarrier::UpdateSpriteAsset(int newLevelNumber)
{
	//checks what input equals to change side barrier to desired look for level
	if (newLevelNumber == 1 || newLevelNumber == 2)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level1SideBarrier_PNG.png"));
	}
	else if (newLevelNumber == 3 || newLevelNumber == 4)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level2SideBarrier_PNG.png"));
	}
	else if (newLevelNumber == 5 || newLevelNumber == 6)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level3SideBarrier_PNG.png"));
	}
	else
	{
		//error...
	}
}


