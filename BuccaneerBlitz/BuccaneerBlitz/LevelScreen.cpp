#include "LevelScreen.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, levelNumber(2)
	, gameRunning(true)
	, player(newGamePointer->GetWindow(), this)
	, sideBarrierLeft(newGamePointer->GetWindow(), &levelNumber)
	, sideBarrierRight(newGamePointer->GetWindow(), &levelNumber)
	, cannonBalls()
	, timer()
	, goons()
	, background(newGamePointer->GetWindow())
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	//debug
	std::cout << cannonBalls.size() << std::endl;
	std::cout << goons.size() << std::endl;



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
			if (cannonBalls[i] != nullptr)
			{
				cannonBalls[i]->Update(frameTime);
				cannonBalls[i]->SetColliding(false);
			}
		}
		for (size_t i = 0; i < goons.size(); i++)
		{
			if (goons[i] != nullptr)
			{
				goons[i]->Update(frameTime);
				goons[i]->SetColliding(false);
			}
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
			for (size_t j = 0; j < goons.size(); j++)
			{
				if (cannonBalls[i] != nullptr && goons[j] != nullptr)
				{
					if (cannonBalls[i]->CheckColliding(*goons[j]))
					{
						cannonBalls[i]->SetColliding(true);
						goons[j]->SetColliding(true);
						cannonBalls[i]->HandleCollision(*goons[j]);
						goons[j]->HandleCollision(*cannonBalls[i]);
					}
				}

			}
			
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
		if (cannonBalls[i] != nullptr)
		{
			if (cannonBalls[i]->GetPosition().y > 0)
			{
				cannonBalls[i]->Draw(target);
			}
			else if (cannonBalls[i]->GetAlive() == false)
			{
				delete cannonBalls[i];
				cannonBalls[i] = nullptr;
				cannonBalls.erase(cannonBalls.begin() + i);
				i--;
			}
			else if (cannonBalls[i]->GetPosition().y < 0)
			{
				if (cannonBalls[i] != nullptr)
				{
					//TODO: Clean up cannonballs once they pass the top of window
					delete cannonBalls[i];
					cannonBalls[i] = nullptr;
					cannonBalls.erase(cannonBalls.begin() + i);
					i--;
				}
			}
		}
		
	}
	for (size_t i = 0; i < goons.size(); i++)
	{
		if (goons[i] != nullptr)
		{
			if (goons[i]->GetPosition().y < background->getSize().y)
			{
				goons[i]->Draw(target);
			}
			else if (goons[i]->GetAlive() == false)
			{
				delete goons[i];
				goons[i] = nullptr;
				goons.erase(goons.begin() + i);
				i--;
			}
			else if (goons[i]->GetPosition().y >= background->getSize().y)
			{
				if (goons[i] != nullptr)
				{
					//TODO: Clean up goons once they pass the top of window
					goons[i] = nullptr;
					delete goons[i];
					goons.erase(goons.begin() + i);
					i--;
				}
			}
		}
	}
	player.Draw(target);
	timer.Draw(target);
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
		cannonBalls.back()->SetPosition(player.GetPosition().x + player.GetWidth() / 2, player.GetPosition().y);
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

void LevelScreen::SpawnEnemy(EnemyType enemyType)
{
	//limits of level space
	float xPosMin = 0 + sideBarrierLeft.GetWidth() / 2;
	float xPosMax = background->getSize().x - sideBarrierRight.GetWidth() / 2;

	//spawns enemy type decided by the function parameters when called
	switch (enemyType)
	{
	case GOON:
			goons.push_back(new Goon(this));
			goons.back()->SetPosition(RandomNumGen(xPosMin, xPosMax), 0 - goons.back()->GetHeight());
		break;

	case CHARGER:

		break;

	case SPRAYER:
		
		break;

	default:
		break;
	}
	cooldownClock.restart();
}

int LevelScreen::RandomNumGen(int min, int max)
{
	int randNum;
	randNum = std::rand() % max + min;

	return randNum;
}

void LevelScreen::Restart()
{
	sideBarrierLeft.ResetPosition("left");
	sideBarrierRight.ResetPosition("right");
	player.SetPosition(background->getSize().x / 2 - player.GetWidth() / 2, 200);
	timer.SetPosition(background->getSize().x - 250, 10);
	goons.push_back(new Goon(this));

	gameRunning = true;
}

