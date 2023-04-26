#include "Text.h"

Text::Text()
	: text()
	, position()
{
}

sf::Vector2f Text::GetPosition()
{
	return position;
}

void Text::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	text.setPosition(newPosition);
}

void Text::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

float Text::GetHeight()
{
	return text.getLocalBounds().height;
}

float Text::GetWidth()
{
	return text.getLocalBounds().height;
}
