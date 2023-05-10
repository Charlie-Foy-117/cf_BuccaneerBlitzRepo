#include "BossScreen.h"
#include "Game.h"

BossScreen::BossScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, bossRoom1Barrier(newGamePointer->GetWindow())
{
	
}

void BossScreen::Update(sf::Time frameTime)
{
}

void BossScreen::Draw(sf::RenderTarget& target)
{
	bossRoom1Barrier.Draw(target);
}

void BossScreen::TriggerEndState()
{
}
