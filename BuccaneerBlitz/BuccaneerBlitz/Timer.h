#pragma once
#include <SFML/Graphics.hpp>

class Timer
{
public:

	Timer();
	void Draw(sf::RenderTarget& target);
	void LevelTimer();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	float GetWidth();
	float GetHeight();

private:

	sf::Text timerText;
	sf::Clock gameTime;
	float levelDuration;

	sf::Vector2f position;
};

