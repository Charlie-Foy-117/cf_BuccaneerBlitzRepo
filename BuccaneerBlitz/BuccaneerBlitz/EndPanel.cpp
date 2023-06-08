#include "EndPanel.h"
#include "AssetManager.h"
#include "Easing.h"

EndPanel::EndPanel(sf::RenderWindow* newWindow)
	: background()
	, title()
	, message()
	, continueMsg()
	, position()
	, window(newWindow)
	, animatingIn(false)
	, animationClock()
{
	background.setTexture(AssetManager::RequestTexture("Assets/Graphics/UI/cf_Panel_PNG.png"));
	background.setScale(1.5f, 1.5f);

	title.setFont(AssetManager::RequestFont("Assets/Graphics/UI/Font/PublicPixel-z84yD.ttf"));
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::Black);

	message.setFont(AssetManager::RequestFont("Assets/Graphics/UI/Font/PublicPixel-z84yD.ttf"));
	message.setCharacterSize(100);
	message.setFillColor(sf::Color::Black);

	continueMsg.setFont(AssetManager::RequestFont("Assets/Graphics/UI/Font/PublicPixel-z84yD.ttf"));
	continueMsg.setCharacterSize(50);
	continueMsg.setFillColor(sf::Color::Black);
	continueMsg.setString("Press 'Bottom Right' to continue");

	ResetPosition();
}

void EndPanel::Update(sf::Time frameTime)
{
	if (animatingIn)
	{
		float xPos = window->getSize().x / 2.0f - background.getGlobalBounds().width / 2.0f;
		float yPos = window->getSize().y;
		float finalYPos = window->getSize().y / 2.0f - background.getGlobalBounds().height / 2.0f;

		//set start and end positions
		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);

		//set duration of the animation
		float duration = 1.0f;
		float time = animationClock.getElapsedTime().asSeconds();

		sf::Vector2f newPosition = Easing::EaseOutQuad(begin, change, duration, time);

		SetPosition(newPosition);

		if (time >= duration)
		{
			SetPosition(begin + change);
			animatingIn = false;
		}
	}
}

void EndPanel::Draw(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(continueMsg);
	target.draw(message);
	target.draw(title);
}

void EndPanel::SetPosition(sf::Vector2f newPosition)
{
	background.setPosition(newPosition);

	//centre the title on the x direction
	float titleX = background.getGlobalBounds().width / 2.0f - title.getGlobalBounds().width / 2.0f;
	title.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 100));

	float messageX = background.getGlobalBounds().width / 2.0f - message.getGlobalBounds().width / 2.0f;
	float messageY = background.getGlobalBounds().height / 2.0f - message.getGlobalBounds().height / 2.0f;
	message.setPosition(sf::Vector2f(newPosition.x + messageX, newPosition.y + messageY));

	float continueMsgX = background.getGlobalBounds().width / 2.0f - continueMsg.getGlobalBounds().width / 2.0f;
	float continueMsgY = background.getGlobalBounds().height / 2.0f - continueMsg.getGlobalBounds().height / 2.0f;
	continueMsg.setPosition(sf::Vector2f(newPosition.x + continueMsgX, newPosition.y + continueMsgY + 250));
}

void EndPanel::StartAnimation()
{
	animatingIn = true;
	animationClock.restart();
}

void EndPanel::ResetPosition()
{
	//reset position back to starting position
	float xPos = window->getSize().x / 2.0f - background.getGlobalBounds().width / 2.0f;
	float yPos = window->getSize().y;
	SetPosition(sf::Vector2f(xPos, yPos));
}

void EndPanel::WinLossPanel(bool alive)
{
	//checks what message to display depending on the players current life status
	if (alive)
	{
		title.setString("You Win!");
	}
	if (!alive)
	{
		title.setString("Out of Lives");
	}
}

void EndPanel::AddScoreToString(int score)
{
	//converts score to string to display
	std::string scoreString = "Score: ";
	scoreString += std::to_string((int)ceil(score));
	message.setString(scoreString);
}
