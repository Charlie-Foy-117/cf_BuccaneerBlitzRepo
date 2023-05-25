#include "SpriteObject.h"
#include "VectorHelper.h"
#include "AssetManager.h"

SpriteObject::SpriteObject()
	: sprite()
	, sound()
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
	lives += lifeValue;
	if (lives < 1)
	{
		lives = 0;
		SetAlive(false);
	}
	else if (lifeValue >= 0 && lives > 3)
	{
		lives = 3;
	}
}
