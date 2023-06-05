#include "SpriteObject.h"
#include "VectorHelper.h"
#include "AssetManager.h"

SpriteObject::SpriteObject()
	: sprite()
	, position(0, 0)
	, alive(true)
	, lives(1)
{
}

void SpriteObject::Update(sf::Time frameTime)
{

}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	if (!alive)
	{
		return;
	}

	target.draw(sprite);
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void SpriteObject::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

void SpriteObject::SetSpriteScale(float xScale, float yScale)
{
	sprite.setScale(xScale, yScale);
}

float SpriteObject::GetHeight()
{
	return sprite.getLocalBounds().height;
}

float SpriteObject::GetWidth()
{
	return sprite.getLocalBounds().width;
}

void SpriteObject::SetAlive(bool newAlive)
{
	alive = newAlive;
}

bool SpriteObject::GetAlive()
{
	return alive;
}

int SpriteObject::GetLives()
{
	return lives;
}

void SpriteObject::ModifyLives(int lifeValue)
{
	//adds value to lives
	lives += lifeValue;
	//if lives is less than 1 then set object to dead
	if (lives < 1)
	{
		lives = 0;
		SetAlive(false);
	}
	//if lives are more than 3 reset back to 3
	else if (lifeValue > 0 && lives > 3)
	{
		lives = 3;
	}
}
