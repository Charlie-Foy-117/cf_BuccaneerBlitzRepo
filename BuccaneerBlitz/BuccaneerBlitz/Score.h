#pragma once
#include "Text.h"

class Score:
	public Text
{
public:

	Score();
	void Draw(sf::RenderTarget& target);
	void ScoreCounter();

	void AddScore(int newScore);
	int GetScore();

private:

	int score;

};
