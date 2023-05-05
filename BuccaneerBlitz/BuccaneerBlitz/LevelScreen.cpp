#include "LevelScreen.h"
#include "Player.h"
#include "Game.h"
#include "Timer.h"
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, levelStageNumber(1)
	, gameRunning(true)
	, player(newGamePointer->GetWindow(), this)
	, sideBarrierLeft(newGamePointer->GetWindow(), &levelStageNumber)
	, sideBarrierRight(newGamePointer->GetWindow(), &levelStageNumber)
	, cannonBalls()
	, enemyCannonBalls()
	, timer(this)
	, score()
	, lifeUI()
	, goons()
	, chargers()
	, pirateBarricades()
	, endPanel(newGamePointer->GetWindow())
	, background(newGamePointer->GetWindow())
	, cooldownClocks()
	, lifePickups()
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	std::cout << chargers.size() << std::endl;
	//changing colour of background
	BackgroundColour(levelStageNumber);

	//when game is running
	if (gameRunning)
	{
		if (player.GetAlive() != true)
		{
			gameRunning = false;
			TriggerEndState();
		}
		else
		{
			//cooldown clocks
			cooldownClocks.push_back(new sf::Clock());
			cooldownClocks.push_back(new sf::Clock());
			cooldownClocks.push_back(new sf::Clock());

			//spawn objects on cooldown
				//goons - Clock 0
				if (cooldownClocks[0]->getElapsedTime().asSeconds() > goons.back()->GetSpawnTime())
				{
					SpawnEnemy(EnemyType::GOON);
				}
				//chargers - Clock 1
				if (cooldownClocks[1]->getElapsedTime().asSeconds() > chargers.back()->GetSpawnTime())
				{
					SpawnEnemy(EnemyType::CHARGER);
				}
				//Sprayers - Clock 2


			//set all objects to not colliding and update every frame
			player.SetAlive(true);
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

			for (size_t i = 0; i < chargers.size(); i++)
			{
				if (chargers[i] != nullptr)
				{
					chargers[i]->Update(frameTime);
					chargers[i]->SetColliding(false);
				}
			}

			for (size_t i = 0; i < pirateBarricades.size(); i++)
			{
				if (pirateBarricades[i] != nullptr)
				{
					pirateBarricades[i]->Update(frameTime);
					pirateBarricades[i]->SetColliding(false);
				}
			}

			for (size_t i = 0; i < lifePickups.size(); i++)
			{
				if (lifePickups[i] != nullptr)
				{
					lifePickups[i]->Update(frameTime);
					lifePickups[i]->SetColliding(false);
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
			for (size_t i = 0; i < goons.size(); i++)
			{
				if (sideBarrierRight.CheckColliding(*goons[i]))
				{
					goons[i]->SetAlive(false);
					goons[i]->HandleCollision(sideBarrierRight);
					sideBarrierRight.HandleCollision(*goons[i]);
				}
				if (sideBarrierLeft.CheckColliding(*goons[i]))
				{
					goons[i]->SetAlive(false);
					goons[i]->HandleCollision(sideBarrierLeft);
					sideBarrierLeft.HandleCollision(*goons[i]);
				}
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
			for (size_t i = 0; i < goons.size(); i++)
			{
				if (goons[i] != nullptr)
				{
					if (player.CheckColliding(*goons[i]))
					{
						player.SetColliding(true);
						goons[i]->SetColliding(true);
						player.HandleCollision(*goons[i]);
						goons[i]->HandleCollision(player);
					}
				}
			}
			for (size_t i = 0; i < chargers.size(); i++)
			{
				if (chargers[i] != nullptr)
				{
					if (player.CheckColliding(*chargers[i]))
					{
						player.SetColliding(true);
						chargers[i]->SetColliding(true);
						player.HandleCollision(*chargers[i]);
						chargers[i]->HandleCollision(player);
					}
				}
			}
			for (size_t i = 0; i < lifePickups.size(); i++)
			{
				if (lifePickups[i] != nullptr)
				{
					if (player.CheckColliding(*lifePickups[i]))
					{
						player.SetColliding(true);
						chargers[i]->SetColliding(true);
						player.HandleCollision(*lifePickups[i]);
						lifePickups[i]->HandleCollision(player);
					}
				}
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
							goons[i]->HandleCollision(*cannonBalls[i]);
						}
					}

				}

				for (size_t k = 0; k < chargers.size(); k++)
				{
					if (cannonBalls[i] != nullptr && chargers[k] != nullptr)
					{
						if (cannonBalls[i]->CheckColliding(*chargers[k]))
						{
							score.AddScore(20);
							cannonBalls[i]->SetColliding(true);
							chargers[k]->SetColliding(true);
							cannonBalls[i]->HandleCollision(*chargers[k]);
							chargers[i]->HandleCollision(*cannonBalls[i]);
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
	}
	//when game is not running i.e. win/loss state
	else
	{
		endPanel.Update(frameTime);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	sideBarrierLeft.Draw(target);
	sideBarrierRight.Draw(target);

	//CheckExistence(cannonBalls, "up", target);
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
			//checks to see if goon is on screen 
			if (goons[i]->GetPosition().y < background->getSize().y)
			{
				//draws goon
				goons[i]->Draw(target);
			}
			//checks if goon is still alive
			else if (goons[i]->GetAlive() == false)
			{
				//clears goon memory and deletes it from vector
				delete goons[i];
				goons[i] = nullptr;
				goons.erase(goons.begin() + i);
				i--;
			}
			//checks to see if position of goon is off screen
			else if (goons[i]->GetPosition().y >= background->getSize().y)
			{
				if (goons[i] != nullptr)
				{
					//clears goon memory and deletes it from vector
					goons[i] = nullptr;
					delete goons[i];
					goons.erase(goons.begin() + i);
					i--;
				}
			}
		}
	}
	for (size_t i = 0; i < chargers.size(); i++)
	{
		if (chargers[i] != nullptr)
		{
			if (chargers[i]->GetPosition().y < background->getSize().y)
			{
				chargers[i]->Draw(target);
			}
			else if (chargers[i]->GetAlive() == false)
			{
				if (chargers.size() - 1 > 0)
				{
					delete chargers[i];
					chargers[i] = nullptr;
					chargers.erase(chargers.begin() + i);
					i--;
				}
				else
				{
					break;
				}
			}
			else if (chargers[i]->GetPosition().y >= background->getSize().y)
			{
				if (chargers[i] != nullptr)
				{
					if (chargers.size() - 1 > 0)
					{
						delete chargers[i];
						chargers[i] = nullptr;
						chargers.erase(chargers.begin() + i);
						i--;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	
	/*for (size_t i = 0; i < pirateBarricades.size(); i++)
	{
		if (pirateBarricades[i] != nullptr)
		{
			if (pirateBarricades[i]->GetPosition().y < background->getSize().y)
			{
				pirateBarricades[i]->Draw(target);
			}
			else if (pirateBarricades[i]->GetAlive() == false)
			{
				//delete pirateBarricades[i];
				//pirateBarricades[i] = nullptr;
				//pirateBarricades.erase(pirateBarricades.begin() + i);
				//i--;
			}
			else if (pirateBarricades[i]->GetPosition().y >= background->getSize().y)
			{
				if (pirateBarricades[i] != nullptr)
				{
					//pirateBarricades[i] = nullptr;
					//delete pirateBarricades[i];
					//pirateBarricades.erase(pirateBarricades.begin() + i);
					//i--;
				}
			}
		}
	}*/
	player.Draw(target);
	timer.Draw(target);
	score.Draw(target);
	for (size_t i = 0; i < player.GetLives(); i++)
	{
		lifeUI.Draw(target);
		lifeUI.SetPosition(0 + (i * lifeUI.GetWidth() / 2), 10);
	}

	for (size_t i = 0; i < lifePickups.size(); i++)
	{
		if (lifePickups[i] != nullptr)
		{
			if (lifePickups[i]->GetAlive() == false)
			{
				delete lifePickups[i];
				lifePickups[i] = nullptr;
				lifePickups.erase(lifePickups.begin() + i);
				i--;
			}
			else
			{
				lifePickups[i]->Draw(target);
			}
		}
	}

	//if game is not running draw endpanel
	if (!gameRunning)
	{
		endPanel.Draw(target);
	}
}

void LevelScreen::BackgroundColour(int currentLevel)
{
	//checks what input equals to change background colour to desired colour for level
	if (currentLevel == 1 || currentLevel == 2) 
	{
		background->clear(sf::Color(38, 73, 202, 255));
	}
	else if (currentLevel == 3 || currentLevel == 4) 
	{
		background->clear(sf::Color(80, 104, 63, 255));
	}
	else if (currentLevel == 5 || currentLevel == 6)
	{
		background->clear(sf::Color(0, 0, 0, 255));
	}
	else
	{
		//error...
	}
}

void LevelScreen::TriggerEndState()
{
	endPanel.WinLossPanel(player.GetAlive());
	endPanel.AddScoreToString(score.GetScore());
	endPanel.StartAnimation();
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
			cooldownClocks[0]->restart();
		break;

	case EnemyType::CHARGER:
			chargers.push_back(new Charger(this, &player));
			chargers.back()->SetPosition(background->getSize().x / 2, 0 - chargers.back()->GetHeight());
			cooldownClocks[1]->restart();
		break;

	case EnemyType::SPRAYER:
		
		break;

	default:
		break;
	}
}

void LevelScreen::SpawnHazard(HazardType hazardType)
{
	switch (hazardType)
	{
	case HazardType::PIRATEBARRICADE:
		pirateBarricades.push_back(new PirateBarricade(this));
		pirateBarricades.back()->SetPosition(background->getSize().x / 2 - pirateBarricades.back()->GetWidth() / 2, 0 - pirateBarricades.back()->GetHeight());
		break;
	case HazardType::SMALLISLAND:
		break;
	default:
		break;
	}
}

void LevelScreen::SpawnPickUp(PickupType pickupType, SpriteObject& spriteCaller)
{
	switch (pickupType)
	{
	case PickupType::LIFE:
		lifePickups.push_back(new LifePickup());
		lifePickups.back()->SetPosition(spriteCaller.GetPosition());
		break;
	case PickupType::ANCHOR:

		break;
	case PickupType::MULTIFIRE:

		break;
	default:
		break;
	}
}

void LevelScreen::CheckExistence(std::vector<SpriteObject*> spriteCaller, std::string direction, sf::RenderTarget& target)
{
	//check what direction the sprite is moving
	//if moving up screen go in here
	if (direction == "up")
	{
		for (size_t i = 0; i < spriteCaller.size(); i++)
		{
			if (spriteCaller[i] != nullptr)
			{
				if (spriteCaller[i]->GetPosition().y > 0)
				{
					spriteCaller[i]->Draw(target);
				}
				else if (spriteCaller[i]->GetAlive() == false)
				{
					delete spriteCaller[i];
					spriteCaller[i] = nullptr;
					spriteCaller.erase(spriteCaller.begin() + i);
					i--;
				}
				else if (spriteCaller[i]->GetPosition().y <= 0)
				{
					if (spriteCaller[i] != nullptr)
					{
						spriteCaller[i] = nullptr;
						delete spriteCaller[i];
						spriteCaller.erase(spriteCaller.begin() + i);
						i--;
					}
				}
			}
		}
	}
	//if moving down screen go in here
	if (direction == "down")
	{
		for (size_t i = 0; i < spriteCaller.size(); i++)
		{
			if (spriteCaller[i] != nullptr)
			{
				if (spriteCaller[i]->GetPosition().y < background->getSize().y)
				{
					spriteCaller[i]->Draw(target);
				}
				else if (spriteCaller[i]->GetAlive() == false)
				{
					delete spriteCaller[i];
					spriteCaller[i] = nullptr;
					spriteCaller.erase(spriteCaller.begin() + i);
					i--;
				}
				else if (spriteCaller[i]->GetPosition().y >= background->getSize().y)
				{
					if (spriteCaller[i] != nullptr)
					{
						spriteCaller[i] = nullptr;
						delete spriteCaller[i];
						spriteCaller.erase(spriteCaller.begin() + i);
						i--;
					}
				}
			}
		}
	}
	else
	{
		//do nothing
	}
}

int LevelScreen::RandomNumGen(int min, int max)
{
	int randNum;
	randNum = std::rand() % max + min;

	return randNum;
}

void LevelScreen::LoadLevel(int currentStage)
{

}

void LevelScreen::Restart()
{
	sideBarrierLeft.ResetPosition("left");
	sideBarrierRight.ResetPosition("right");
	player.SetPosition(background->getSize().x / 2 - player.GetWidth() / 2, 600);
	timer.SetPosition((float)background->getSize().x - 250, 10);
	score.SetPosition((float)background->getSize().x - 300, timer.GetPosition().y + 200);



	//test vectors
	goons.push_back(new Goon(this));
	goons.back()->SetPosition(background->getSize().x / 2, 0);
	chargers.push_back(new Charger(this, &player));
	chargers.back()->SetPosition(background->getSize().x / 2, 0 - chargers.back()->GetHeight());
	//pirateBarricades.push_back(new PirateBarricade(this));
	//pirateBarricades.back()->SetPosition(background->getSize().x / 2 - pirateBarricades.back()->GetWidth() + pirateBarricades.back()->GetWidth(), 0 - pirateBarricades.back()->GetHeight());



	gameRunning = true;
}

