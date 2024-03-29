#pragma once
#include <SFML/Graphics.hpp>
class Game;

class Screen
{
public:

	Screen(Game* newGamePointer);

	virtual ~Screen();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

private:

	Game* gamePointer;
};

