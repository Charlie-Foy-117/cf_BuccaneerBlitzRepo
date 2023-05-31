#include "SideBarrier.h"
#include "AssetManager.h"

SideBarrier::SideBarrier(sf::RenderWindow* newWindow, int* newLevelNumber)
	: PhysicsObject()
	, levelNumber(newLevelNumber)
	, window(newWindow)
{
	ResetPosition("left");
	ResetPosition("right");

}

void SideBarrier::ResetPosition(std::string side)
{
	float xPos = window->getSize().x - sprite.getGlobalBounds().width;
	float yPos = window->getSize().y / 2.0f - sprite.getGlobalBounds().height / 2.0f;
	if (side == "left")
	{
		//sets position to left sdie of screen
		SetPosition(sf::Vector2f(0, 0));
		sprite.setScale(1.0f, 1.05f);
		UpdateSpriteAsset(*levelNumber, "left");
	}
	if (side == "right")
	{
		//sets position to right side of screen
		sprite.setScale(1.0f, 1.05f);
		SetPosition(sf::Vector2f(xPos, 0));
		UpdateSpriteAsset(*levelNumber, "right");

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

void SideBarrier::UpdateSpriteAsset(int newLevelNumber, std::string side)
{
	//checks what input equals to change side barrier to desired look for level
	if (side == "left")
	{
		if (newLevelNumber == 1 || newLevelNumber == 2)
		{
			sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level1SideBarrierFlipped_PNG.png"));
		}
		else if (newLevelNumber == 3 || newLevelNumber == 4)
		{
			sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level2SideBarrierFlipped_PNG.png"));
		}
		else if (newLevelNumber == 5 || newLevelNumber == 6)
		{
			sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_Level3SideBarrierFlipped_PNG.png"));
		}
		else
		{
			//error...
		}
	}
	else if (side == "right")
	{
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
}


