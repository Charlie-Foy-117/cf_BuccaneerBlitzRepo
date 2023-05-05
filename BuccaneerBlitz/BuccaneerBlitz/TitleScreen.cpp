#include "TitleScreen.h"
#include "Game.h"

TitleScreen::TitleScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, game(newGamePointer)
	, window(newGamePointer->GetWindow())
	, text()
	, cooldownTimer()
	, cooldown(0.1f)
{
	text.SetText("Press 'L' to start");
	text.SetPosition(game->GetWindow()->getSize().x / 2 - text.GetWidth() / 2, 40);
}

void TitleScreen::Update(sf::Time frameTime)
{
	window->clear();

	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			game->ChangeGameState(GameState::LEVELSCREEN);
		}
		cooldownTimer.restart();
	}
}

void TitleScreen::Draw(sf::RenderTarget& target)
{
	text.Draw(target);
}
