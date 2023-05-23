#pragma once
#include <SFML/Graphics.hpp>
class EndPanel
{
public:

	EndPanel(sf::RenderWindow* newWindow);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

	void SetPosition(sf::Vector2f newPosition);

	void StartAnimation();
	void ResetPosition();
	void WinLossPanel(bool alive);
	void AddScoreToString(int score);

private:

	sf::Sprite background;
	sf::Text title;
	sf::Text message;
	sf::Text continueMsg;
	sf::Vector2f position;
	sf::RenderWindow* window;

	bool animatingIn;
	sf::Clock animationClock;
};

