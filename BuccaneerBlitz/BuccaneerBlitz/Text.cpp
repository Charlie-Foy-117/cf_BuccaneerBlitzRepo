#include "Text.h"
#include "AssetManager.h"

Text::Text()
	: text()
	, position()
{
	text.setFont(AssetManager::RequestFont("Assets/Graphics/UI/Font/PublicPixel-z84yD.ttf"));
}

void Text::Draw(sf::RenderTarget& target)
{
	target.draw(text);
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

void Text::SetText(std::string newText)
{
	text.setString(newText);
}
