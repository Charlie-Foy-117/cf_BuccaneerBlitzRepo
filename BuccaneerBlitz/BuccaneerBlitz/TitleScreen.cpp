#include "TitleScreen.h"
#include "Game.h"

TitleScreen::TitleScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, game(newGamePointer)
	, window(newGamePointer->GetWindow())
	, text()
	, scoreText()
	, score()
	, cooldownTimer()
	, cooldown(0.1f)
{
	text.SetText("Press '6' to start");
	text.SetPosition(10, 40);
	scoreText.SetText("Highscore: " + std::to_string(score.LoadHighScore()));
	scoreText.SetPosition(10, 140);
	toolTip.SetText("'6' = cannonball, '4' = anchor, '5' = multifire");
	toolTip.SetPosition(10, 1000);

	overlay.SetPosition(overlay.GetPosition().x, window->getSize().y - overlay.GetHeight() * 2.4f);
	titleCard.SetPosition(window->getSize().x - titleCard.GetWidth() * 2.3f, -30);

	buoy.SetPosition(100, 100);
}

TitleScreen::~TitleScreen()
{
	Screen::~Screen();
}

void TitleScreen::Update(sf::Time frameTime)
{
	window->clear();

	//stops game from instantly restarting on input press
	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		//if input is pressed change screen to level screen
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		{
			game->ChangeGameState(GameState::LEVELSCREEN);
		}
		cooldownTimer.restart();
	}
}

void TitleScreen::Draw(sf::RenderTarget& target)
{
	backplate.Draw(target);
	buoy.Draw(target);
	overlay.Draw(target);
	titleCard.Draw(target);
	text.Draw(target);
	scoreText.Draw(target);
	toolTip.Draw(target);
}
