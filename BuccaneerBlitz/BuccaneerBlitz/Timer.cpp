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
	if (levelScreen->gameRunning)
	{
		remainingTime = levelDuration - gameTime.getElapsedTime().asSeconds();
		std::string timerString = "Time: ";

		if (remainingTime <= 0)
		{
			//todo: change level to boss room 
			ResetTime();
			if (levelScreen->levelStageNumber == 1 || levelScreen->levelStageNumber == 3 || levelScreen->levelStageNumber == 5)
			{
				if (levelScreen->levelStageNumber <= 5)
				{
					levelScreen->levelStageNumber++;
				}
			}
			//change timer to go up for infinite time

		}

		timerString += std::to_string((int)ceil(remainingTime));
		text.setString(timerString);
	}
	else
	{
		text.setString("GAMEOVER");
	}
}

void Timer::ResetTime()
{
	gameTime.restart();
	remainingTime = levelDuration;
}
