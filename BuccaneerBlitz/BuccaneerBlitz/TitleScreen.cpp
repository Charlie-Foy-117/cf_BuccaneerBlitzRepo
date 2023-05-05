#include "TitleScreen.h"
#include "Game.h"

TitleScreen::TitleScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, game(newGamePointer)
	, text()
{
	text.SetText("Press 'L' to start");
	text.SetPosition(game->GetWindow()->getSize().x / 2 - text.GetWidth() / 2, 40);
}

void TitleScreen::Update(sf::Time frameTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		game->PlayLevel();
	}
}

void TitleScreen::Draw(sf::RenderTarget& target)
{
	text.Draw(target);
}
