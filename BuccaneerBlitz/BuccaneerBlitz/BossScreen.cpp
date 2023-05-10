#include "BossScreen.h"
#include "Game.h"
#include "LevelScreen.h"

BossScreen::BossScreen(Game* newGamePointer, LevelScreen* newLevelScreen)
	: Screen(newGamePointer)
	, bossRoom1Barrier(newGamePointer->GetWindow())
	, player(newGamePointer->GetWindow(), newLevelScreen)
	, timer(newLevelScreen)
	, score()
	, lifeUI()
	, anchorUI()
	, levelScreen(newLevelScreen)
	, game(newGamePointer)
{

}

void BossScreen::Update(sf::Time frameTime)
{
	//changing colour of background
	levelScreen->BackgroundColour(levelScreen->levelStageNumber);

	player.SetAlive(true);
	player.Update(frameTime);
	player.SetColliding(false);
}

void BossScreen::Draw(sf::RenderTarget& target)
{
	bossRoom1Barrier.Draw(target);
	score.Draw(target);
	score.SetPosition(sf::Vector2f(600, 600));
	timer.Draw(target);
	player.Draw(target);
	lifeUI.Draw(target);
	anchorUI.Draw(target);
}

void BossScreen::TriggerEndState()
{
}
