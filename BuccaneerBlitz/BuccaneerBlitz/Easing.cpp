#include "Easing.h"

sf::Vector2f Easing::EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
	return -change * time / duration * ((time / duration) - 2) + begin;
}