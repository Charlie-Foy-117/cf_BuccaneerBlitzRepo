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
	//only displays time if game in running
	if (levelScreen->gameRunning)
	{
		if (levelScreen->levelStageNumber == 2 || levelScreen->levelStageNumber == 4 || levelScreen->levelStageNumber == 6)
		{
			//if level is 2, 4, 6 timer will go up until level goes up
			remainingTime = gameTime.getElapsedTime().asSeconds();
			std::string timerString = "Time: ";
			timerString += std::to_string((int)ceil(remainingTime));
			text.setString(timerString);
		}
		else
		{
			//accesses if game is on level 1
			if (levelScreen->levelStageNumber == 1)
			{
				//set duration of level
				levelDuration = 60.0f;
				if (remainingTime <= 0)
				{
					//once time hits 0 reset time and move up a level
					ResetTime();
					levelScreen->levelStageNumber++;
				}
			}
			//accesses if game is on level 3
			if (levelScreen->levelStageNumber == 3)
			{
				//set duration of level
				levelDuration = 90.0f;
				if (remainingTime <= 0)
				{
					//once time hits 0 reset time and move up a level
					ResetTime();
					levelScreen->levelStageNumber++;
				}
			}
			//accesses if game is on level 5
			if (levelScreen->levelStageNumber == 5)
			{
				//set duration of level
				levelDuration = 120.0f;
				if (remainingTime <= 0)
				{
					//once time hits 0 reset time and move up a level
					ResetTime();
					levelScreen->levelStageNumber++;
				}
			}

			if (levelScreen->levelStageNumber == 1 || levelScreen->levelStageNumber == 3 || levelScreen->levelStageNumber == 5)
			{
				//if level is 1, 3, 5 timer will go down towards 0
				remainingTime = levelDuration - gameTime.getElapsedTime().asSeconds();
				std::string timerString = "Time: ";
				timerString += std::to_string((int)ceil(remainingTime));
				text.setString(timerString);
			}
		}
	}
	else
	{
		//when game is over time changes string to gameover
		text.setString("GAMEOVER");
	}
}

void Timer::ResetTime()
{
	gameTime.restart();
	//resets remaining time to initial duration
	remainingTime = levelDuration;
}

sf::Clock Timer::GetGameTime()
{
	return gameTime;
}
