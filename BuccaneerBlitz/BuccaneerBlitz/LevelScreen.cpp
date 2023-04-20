#include "LevelScreen.h"
#include "Player.h"
#include "Game.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, gameRunning(true)
	, player(newGamePointer->GetWindow(), this)
	, sideBarrierLeft(newGamePointer->GetWindow())
	, sideBarrierRight(newGamePointer->GetWindow())
	, cannonBalls()
	, background(newGamePointer->GetWindow())
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	//changing colour of background
	background->clear(sf::Color(38, 73, 202, 255));

	//when game is running
	if (gameRunning)
	{
		player.Update(frameTime);
		player.SetColliding(false);
		sideBarrierLeft.SetColliding(false);
		sideBarrierRight.SetColliding(false);
		for (size_t i = 0; i < cannonBalls.size(); i++)
		{
			cannonBalls[i]->Update(frameTime);
			cannonBalls[i]->SetColliding(false);
		}

		//collision updating

		//side barriers
		if (sideBarrierLeft.CheckColliding(player))
		{
			player.SetColliding(true);
			sideBarrierLeft.SetColliding(true);
			player.HandleCollision(sideBarrierLeft);
			sideBarrierLeft.HandleCollision(player);
		}
		if (sideBarrierRight.CheckColliding(player))
		{
			player.SetColliding(true);
			sideBarrierRight.SetColliding(true);
			player.HandleCollision(sideBarrierRight);
			sideBarrierRight.HandleCollision(player);
		}

		//player
		if (player.CheckColliding(sideBarrierLeft))
		{
			player.SetColliding(true);
			sideBarrierLeft.SetColliding(true);
			sideBarrierLeft.HandleCollision(player);
		}
		if (player.CheckColliding(sideBarrierRight))
		{
			player.SetColliding(true);
			sideBarrierRight.SetColliding(true);
			sideBarrierRight.HandleCollision(player);
		}

		//cannonball
		for (size_t i = 0; i < cannonBalls.size(); i++)
		{
			//if(cannonBalls[i]->CheckColliding())
		}


	}
	//when game is not running i.e. win/loss state
	else
	{

	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	sideBarrierLeft.Draw(target);
	sideBarrierRight.Draw(target);

	for (size_t i = 0; i < cannonBalls.size(); i++)
	{
		if (cannonBalls[i]->GetPosition().y > 0)
		{
			cannonBalls[i]->Draw(target);
		}
		else if (cannonBalls[i]->GetPosition().y < 0)
		{
			if (cannonBalls[i] != nullptr)
			{
				//TODO: Clean up cannonballs once they pass the top of window
				//delete cannonBalls[i];
				//cannonBalls[i] = nullptr;
			}
		}
	}

	player.Draw(target);
}

void LevelScreen::TriggerEndState(bool win)
{
}

void LevelScreen::AddToVector(Projectile projectileType)
{
	switch (projectileType)
	{
	case CANNONBALL:
		cannonBalls.push_back(new CannonBall());
		cannonBalls.back()->SetPosition(player.GetPosition().x - player.GetWidth() / 2, player.GetPosition().y + cannonBalls.back()->GetHeight());
		break;

	case ANCHOR:
		//anchor.push_back(new Anchor);
		break;

	case MULTIFIRE:
		for (size_t i = 0; i < 3; i++)
		{
			cannonBalls.push_back(new CannonBall());
		}
		break;

	default:
		break;
	}
}

void LevelScreen::Restart()
{
	sideBarrierLeft.ResetPosition("left");
	sideBarrierRight.ResetPosition("right");
	player.SetPosition(200, 200);

	gameRunning = true;
}
