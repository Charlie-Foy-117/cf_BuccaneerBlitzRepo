#pragma once
#include <SFML/Graphics.hpp>
class Text
{
public:

	Text();

	void Draw(sf::RenderTarget& target);
	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	float GetHeight();
	float GetWidth();

	void SetText(std::string newText);

protected:

	sf::Text text;

private:

	sf::Vector2f position;
};

