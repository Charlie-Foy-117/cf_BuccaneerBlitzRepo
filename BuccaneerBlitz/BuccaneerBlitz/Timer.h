#pragma once
#include "Text.h"

class LevelScreen;

class Timer:
	public Text
{
public:

	Timer(LevelScreen* newLevelScreen);
	void Draw(sf::RenderTarget& target);
	void LevelTimer();
	void ResetTime();

private:

	sf::Clock gameTime;
	float levelDuration;
	float remainingTime;

	LevelScreen* levelScreen;
};

