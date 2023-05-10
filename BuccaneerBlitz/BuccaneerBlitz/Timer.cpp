#include "AssetManager.h"
#include "Timer.h"
#include "LevelScreen.h"

Timer::Timer(LevelScreen* newLevelScreen)
	: Text()
	, gameTime()
	, levelDuration(60.0f)
	, levelScreen(newLevelScreen)
	, remainingTime()
{
	text.setFont(AssetManager::RequestFont("Assets/Graphics/UI/cf_font.ttf"));
}

void Timer::Draw(sf::RenderTarget& target)
{
	target.draw(text);
	LevelTimer();
}

void Timer::LevelTimer()
{
	remainingTime = levelDuration - gameTime.getElapsedTime().asSeconds();
	std::string timerString = "Time: ";

	if (remainingTime <= 0)
	{
		//todo: change level to boss room 
		//levelScreen->levelStageNumber++;
		//change timer to go up for infinite time
		
	}

	timerString += std::to_string((int)ceil(remainingTime));
	text.setString(timerString);
}

void Timer::ResetTime()
{
	remainingTime = levelDuration;
}
