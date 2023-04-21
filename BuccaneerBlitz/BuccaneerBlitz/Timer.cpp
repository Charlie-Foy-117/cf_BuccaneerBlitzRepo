#include "AssetManager.h"
#include "Timer.h"

Timer::Timer()
	: timerText()
	, gameTime()
	, levelDuration(60.0f)
	, position()
{
	timerText.setFont(AssetManager::RequestFont("Assets/Graphics/UI/cf_font.ttf"));
}

void Timer::Draw(sf::RenderTarget& target)
{
	target.draw(timerText);
	LevelTimer();
}

void Timer::LevelTimer()
{
	float remainingTime = levelDuration - gameTime.getElapsedTime().asSeconds();
	std::string timerString = "Time: ";

	if (remainingTime <= 0)
	{
		//todo: change level to boss room 
		//change timer to go up for infinite time
		
	}

	timerString += std::to_string((int)ceil(remainingTime));
	timerText.setString(timerString);
}

sf::Vector2f Timer::GetPosition()
{
	return position;
}

void Timer::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	timerText.setPosition(newPosition);
}

void Timer::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

float Timer::GetWidth()
{
	return timerText.getLocalBounds().width;
}

float Timer::GetHeight()
{
	return timerText.getLocalBounds().height;
}
