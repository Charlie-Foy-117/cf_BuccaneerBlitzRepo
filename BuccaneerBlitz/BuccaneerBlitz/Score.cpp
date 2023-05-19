#include "Score.h"
#include "AssetManager.h"
#include <fstream>

Score::Score()
	: Text()
	, score(0)
{
	text.setFont(AssetManager::RequestFont("Assets/Graphics/UI/Font/PublicPixel-z84yD.ttf"));
}

void Score::Draw(sf::RenderTarget& target)
{
	ScoreCounter();
	target.draw(text);
}

void Score::ScoreCounter()
{
	std::string scoreString = "Score: ";
	scoreString += std::to_string((int)ceil(score));
	text.setString(scoreString);

}

void Score::AddScore(int newScore)
{
	score += newScore;
}

int Score::GetScore()
{
	return score;
}

void Score::ResetScore()
{
	score = 0;
}

void Score::SaveHighScore(int score)
{
	std::ofstream file("highscore.txt");
	if (file.is_open())
	{
		file << score;
		file.close();
	}
}

int Score::LoadHighScore()
{
	std::ifstream file("highscore.txt");
	int score = 0;

	if (file.is_open())
	{
		file >> score;
		file.close();
	}

	return score;
}
