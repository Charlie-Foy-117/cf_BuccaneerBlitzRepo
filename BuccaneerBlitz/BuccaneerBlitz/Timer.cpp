#include "AssetManager.h"
#include "Timer.h"
#include "LevelScreen.h"

Timer::Timer(LevelScreen* newLevelScreen)
	: Text()
	, gameTime()
	, levelDuration(60.0f)
	, levelScreen(newLevelScreen)
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
	float remainingTime = levelDuration - gameTime.getElapsedTime().asSeconds();
	std::string timerString = "Time: ";

	if (remainingTime <= 0)
	{
		//todo: change level to boss room 
		//levelScreen->levelNumber++;
		//change timer to go up for infinite time
		
	}

	timerString += std::to_string((int)ceil(remainingTime));
	text.setString(timerString);
}
