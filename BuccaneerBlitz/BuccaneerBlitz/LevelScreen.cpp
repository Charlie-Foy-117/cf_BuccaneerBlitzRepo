#include "LevelScreen.h"
#include "Player.h"
#include "Game.h"
#include "Timer.h"
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, levelNumber(2)
	, gameRunning(true)
	, player(newGamePointer->GetWindow(), this)
	, sideBarrierLeft(newGamePointer->GetWindow(), &levelNumber)
	, sideBarrierRight(newGamePointer->GetWindow(), &levelNumber)
	, cannonBalls()
	, enemyCannonBalls()
	, timer(this)
	, score()
	, goons()
	, background(newGamePointer->GetWindow())
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	//debug
	std::cout << cannonBalls.size() << std::endl;
	std::cout << enemyCannonBalls.size() << std::endl;
	std::cout << goons.size() << std::endl;



	//when game is running
	if (gameRunning)
	{

		//changing colour of background
		BackgroundColour(levelNumber);

		if (cooldownClock.getElapsedTime().asSeconds() > goons.back()->GetSpawnTime())
		{
			SpawnEnemy(EnemyType::GOON);
		}
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
		for (size_t i = 0; i < enemyCannonBalls.size(); i++)
		{
			if (enemyCannonBalls[i] != nullptr)
			{
				enemyCannonBalls[i]->Update(frameTime);
				enemyCannonBalls[i]->SetColliding(false);
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
						score.AddScore(10);
						cannonBalls[i]->SetColliding(true);
						goons[j]->SetColliding(true);
						cannonBalls[i]->HandleCollision(*goons[j]);
					}
				}

			}
			
		}

		for (size_t i = 0; i < enemyCannonBalls.size(); i++)
		{
			if (enemyCannonBalls[i]->CheckColliding(player))
			{
				enemyCannonBalls[i]->SetColliding(true);
				player.SetColliding(true);
				enemyCannonBalls[i]->HandleCollision(player);
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
			//checks to see if cannonball is on screen 
			if (cannonBalls[i]->GetPosition().y > 0)
			{
				//draws cannonball
				cannonBalls[i]->Draw(target);
			}
			//checks if cannonball is still alive
			if (cannonBalls[i]->GetAlive() == false)
			{
				//clears cannonball memory and deletes it from vector 
				delete cannonBalls[i];
				cannonBalls[i] = nullptr;
				cannonBalls.erase(cannonBalls.begin() + i);
				i--;
			}
			//checks to see if position of cannonball is off screen
			else if (cannonBalls[i]->GetPosition().y <= 0)
			{
				if (cannonBalls[i] != nullptr)
				{
					//clears cannonball memory and deletes it from vector
					delete cannonBalls[i];
					cannonBalls[i] = nullptr;
					cannonBalls.erase(cannonBalls.begin() + i);
					i--;
				}
			}
		}
		
	}
	for (size_t i = 0; i < enemyCannonBalls.size(); i++)
	{
		if (enemyCannonBalls[i] != nullptr)
		{
			//checks to see if cannonball is on screen 
			if (enemyCannonBalls[i]->GetPosition().y < background->getSize().y)
			{
				//draws cannonball
				enemyCannonBalls[i]->Draw(target);
			}
			//checks if cannonball is still alive
			if (enemyCannonBalls[i]->GetAlive() == false)
			{
				//clears cannonball memory and deletes it from vector
				delete enemyCannonBalls[i];
				enemyCannonBalls[i] = nullptr;
				enemyCannonBalls.erase(enemyCannonBalls.begin() + i);
				i--;
			}
			//checks to see if position of cannonball is off screen
			else if (enemyCannonBalls[i]->GetPosition().y >= background->getSize().y)
			{
				if (enemyCannonBalls[i] != nullptr)
				{
					//clears cannonball memory and deletes it from vector
					delete enemyCannonBalls[i];
					enemyCannonBalls[i] = nullptr;
					enemyCannonBalls.erase(enemyCannonBalls.begin() + i);
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
	score.Draw(target);
}

void LevelScreen::BackgroundColour(int currentLevel)
{
	switch (currentLevel)
	{
	case 1:
		background->clear(sf::Color(38, 73, 202, 255));
		break;
	case 2:
		background->clear(sf::Color(80, 104, 63, 255));
		break;
	case 3:
		//background->clear(sf::Color(38, 73, 202, 255));
		break;
	default:
		break;
	}
}

void LevelScreen::TriggerEndState(bool win)
{
}

void LevelScreen::SpawnProjectile(Projectile projectileType, SpriteObject& spriteCaller)
{
	if (spriteCaller.GetAlive() == true)
	{
		switch (projectileType)
		{
		case Projectile::CANNONBALL:
			cannonBalls.push_back(new CannonBall());
			cannonBalls.back()->SetPosition(spriteCaller.GetPosition().x + spriteCaller.GetWidth() / 2, player.GetPosition().y);
			break;

		case Projectile::ANCHOR:
			//anchor.push_back(new Anchor);
			break;

		case Projectile::MULTIFIRE:
			for (size_t i = 0; i < 3; i++)
			{
				cannonBalls.push_back(new CannonBall());
			}
			break;

		case Projectile::ENEMYCANNONBALL:

			enemyCannonBalls.push_back(new CannonBall());
			enemyCannonBalls.back()->SetVelocity(0, 400);
			//todo: set position in front of ships that calls function
			enemyCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + enemyCannonBalls.back()->GetHeight() / 2);

			break;
		default:
			break;
		}
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
	case EnemyType::GOON:
			goons.push_back(new Goon(this));
			goons.back()->SetPosition((float)RandomNumGen((int)xPosMin, (int)xPosMax), 0 - goons.back()->GetHeight());
		break;

	case EnemyType::CHARGER:

		break;

	case EnemyType::SPRAYER:
		
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
	timer.SetPosition((float)background->getSize().x - 250, 10);
	score.SetPosition((float)background->getSize().x - 300, timer.GetPosition().y + 200);
	goons.push_back(new Goon(this));

	gameRunning = true;
}

