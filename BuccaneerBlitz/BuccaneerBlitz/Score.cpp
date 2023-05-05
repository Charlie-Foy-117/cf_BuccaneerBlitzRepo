#include "Score.h"
#include "AssetManager.h"

Score::Score()
	: Text()
	, score(0)
{
	text.setFont(AssetManager::RequestFont("Assets/Graphics/UI/cf_font.ttf"));
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
