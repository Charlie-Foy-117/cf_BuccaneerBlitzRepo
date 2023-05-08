#include "LevelScreen.h"
#include "Player.h"
#include "Game.h"
#include "Timer.h"
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player(newGamePointer->GetWindow(), this)
	, levelStageNumber(1)
	, gameRunning(true)
	, background(newGamePointer->GetWindow())
	, game(newGamePointer)
	, sideBarrierLeft(newGamePointer->GetWindow(), &levelStageNumber)
	, sideBarrierRight(newGamePointer->GetWindow(), &levelStageNumber)
	, charger(this, &player)
	, goon(this)
	, sprayer(this)
	, cannonBalls()
	, anchors()
	, goonCannonBalls()
	, pirateBarricades()
	, timer(this)
	, score()
	, lifeUI()
	, anchorUI()
	, endPanel(newGamePointer->GetWindow())
	, cooldownClocks()
	, goons()
	, chargers()
	, sprayers()
	, lifePickups()
	, anchorPickups()
	, xVelocity(100)
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
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
			if (cooldownClocks[0]->getElapsedTime().asSeconds() > goon.GetSpawnTime())
			{
				SpawnEnemy(EnemyType::GOON);
			}
			//chargers - Clock 1
			if (cooldownClocks[1]->getElapsedTime().asSeconds() > charger.GetSpawnTime())
			{
				SpawnEnemy(EnemyType::CHARGER);
			}
			//Sprayers - Clock 2
			if (cooldownClocks[2]->getElapsedTime().asSeconds() > sprayer.GetSpawnTime())
			{
				SpawnEnemy(EnemyType::SPRAYER);
			}

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

			for (size_t i = 0; i < anchors.size(); i++)
			{
				if (anchors[i] != nullptr)
				{
					anchors[i]->Update(frameTime);
					anchors[i]->SetColliding(false);
				}
			}

			for (size_t i = 0; i < goonCannonBalls.size(); i++)
			{
				if (goonCannonBalls[i] != nullptr)
				{
					goonCannonBalls[i]->Update(frameTime);
					goonCannonBalls[i]->SetColliding(false);
				}
			}

			for (size_t i = 0; i < sprayerCannonBalls.size(); i++)
			{
				if (sprayerCannonBalls[i] != nullptr)
				{
					sprayerCannonBalls[i]->Update(frameTime);
					sprayerCannonBalls[i]->SetColliding(false);
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

			for (size_t i = 0; i < sprayers.size(); i++)
			{
				if (sprayers[i] != nullptr)
				{
					sprayers[i]->Update(frameTime);
					sprayers[i]->SetColliding(false);
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

			for (size_t i = 0; i < anchorPickups.size(); i++)
			{
				if (anchorPickups[i] != nullptr)
				{
					anchorPickups[i]->Update(frameTime);
					anchorPickups[i]->SetColliding(false);
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
			for (size_t i = 0; i < sprayers.size(); i++)
			{
				if (sideBarrierRight.CheckColliding(*sprayers[i]))
				{
					sprayers[i]->SetAlive(false);
					sprayers[i]->HandleCollision(sideBarrierRight);
					sideBarrierRight.HandleCollision(*sprayers[i]);
				}
				if (sideBarrierLeft.CheckColliding(*sprayers[i]))
				{
					sprayers[i]->SetAlive(false);
					sprayers[i]->HandleCollision(sideBarrierLeft);
					sideBarrierLeft.HandleCollision(*sprayers[i]);
				}
			}
			for (size_t i = 0; i < sprayerCannonBalls.size(); i++)
			{
				if (sprayerCannonBalls[i]->CheckColliding(sideBarrierLeft))
				{
					sprayerCannonBalls[i]->SetColliding(true);
					sideBarrierLeft.SetColliding(true);
					sprayerCannonBalls[i]->HandleCollision(sideBarrierLeft);
				}
				if (sprayerCannonBalls[i]->CheckColliding(sideBarrierRight))
				{
					sprayerCannonBalls[i]->SetColliding(true);
					sideBarrierRight.SetColliding(true);
					sprayerCannonBalls[i]->HandleCollision(sideBarrierRight);
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
						lifePickups[i]->SetColliding(true);
						lifePickups[i]->HandleCollision(player);
					}
				}
			}
			for (size_t i = 0; i < anchorPickups.size(); i++)
			{
				if (anchorPickups[i] != nullptr)
				{
					if (player.CheckColliding(*anchorPickups[i]))
					{
						player.SetColliding(true);
						anchorPickups[i]->SetColliding(true);
						player.HandleCollision(*anchorPickups[i]);
						anchorPickups[i]->HandleCollision(player);
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
			}
			for (size_t i = 0; i < cannonBalls.size(); i++)
			{
				for (size_t j = 0; j < chargers.size(); j++)
				{
					if (cannonBalls[i] != nullptr && chargers[j] != nullptr)
					{
						if (cannonBalls[i]->CheckColliding(*chargers[j]))
						{
							score.AddScore(20);
							cannonBalls[i]->SetColliding(true);
							chargers[j]->SetColliding(true);
							cannonBalls[i]->HandleCollision(*chargers[j]);
							chargers[i]->HandleCollision(*cannonBalls[i]);
						}
					}
				}
			}
			for (size_t i = 0; i < cannonBalls.size(); i++)
			{
				for (size_t j = 0; j < sprayers.size(); j++)
				{
					if (cannonBalls[i] != nullptr && sprayers[j] != nullptr)
					{
						if (cannonBalls[i]->CheckColliding(*sprayers[j]))
						{
							score.AddScore(15);
							cannonBalls[i]->SetColliding(true);
							sprayers[j]->SetColliding(true);
							cannonBalls[i]->HandleCollision(*sprayers[j]);
							sprayers[i]->HandleCollision(*cannonBalls[i]);
						}
					}
				}
			}
			

			for (size_t i = 0; i < goonCannonBalls.size(); i++)
			{
				if (goonCannonBalls[i]->CheckColliding(player))
				{
					goonCannonBalls[i]->SetColliding(true);
					player.SetColliding(true);
					goonCannonBalls[i]->HandleCollision(player);
				}
			}
			for (size_t i = 0; i < sprayerCannonBalls.size(); i++)
			{
				if (sprayerCannonBalls[i]->CheckColliding(player))
				{
					sprayerCannonBalls[i]->SetColliding(true);
					player.SetColliding(true);
					sprayerCannonBalls[i]->HandleCollision(player);
				}
			}
		}
	}
	//when game is not running i.e. win/loss state
	else
	{
		endPanel.Update(frameTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			game->ChangeGameState(GameState::TITLESCREEN);
		}
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

				if (cannonBalls.size() - 1 > 0)
				{
					i--;
					break;
				}
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

					if (cannonBalls.size() - 1 > 0)
					{
						i--;
						break;
					}
				}
			}
		}
		
	}
	for (size_t i = 0; i < anchors.size(); i++)
	{
		if (anchors[i] != nullptr)
		{
			//checks to see if cannonball is on screen 
			if (anchors[i]->GetPosition().y > 0)
			{
				//draws cannonball
				anchors[i]->Draw(target);
			}
			//checks if cannonball is still alive
			if (anchors[i]->GetAlive() == false)
			{
				//clears cannonball memory and deletes it from vector 
				delete anchors[i];
				anchors[i] = nullptr;
				anchors.erase(anchors.begin() + i);

				if (anchors.size() - 1 > 0)
				{
					i--;
					break;
				}
			}
			//checks to see if position of cannonball is off screen
			else if (anchors[i]->GetPosition().y <= 0)
			{
				if (anchors[i] != nullptr)
				{
					//clears cannonball memory and deletes it from vector
					delete anchors[i];
					anchors[i] = nullptr;
					anchors.erase(anchors.begin() + i);

					if (anchors.size() - 1 > 0)
					{
						i--;
						break;
					}
				}
			}
		}

	}
	for (size_t i = 0; i < goonCannonBalls.size(); i++)
	{
		if (goonCannonBalls[i] != nullptr)
		{
			//checks to see if cannonball is on screen 
			if (goonCannonBalls[i]->GetPosition().y < background->getSize().y)
			{
				//draws cannonball
				goonCannonBalls[i]->Draw(target);
			}
			//checks if cannonball is still alive
			if (goonCannonBalls[i]->GetAlive() == false)
			{
				//clears cannonball memory and deletes it from vector
				delete goonCannonBalls[i];
				goonCannonBalls[i] = nullptr;
				goonCannonBalls.erase(goonCannonBalls.begin() + i);

				if (goonCannonBalls.size() - 1 > 0)
				{
					i--;
					break;
				}
			}
			//checks to see if position of cannonball is off screen
			else if (goonCannonBalls[i]->GetPosition().y >= background->getSize().y)
			{
				if (goonCannonBalls[i] != nullptr)
				{
					//clears cannonball memory and deletes it from vector
					delete goonCannonBalls[i];
					goonCannonBalls[i] = nullptr;
					goonCannonBalls.erase(goonCannonBalls.begin() + i);

					if (goonCannonBalls.size() - 1 > 0)
					{
						i--;
						break;
					}
				}
			}
		}
	}
	for (size_t i = 0; i < sprayerCannonBalls.size(); i++)
	{
		if (sprayerCannonBalls[i] != nullptr)
		{
			//checks to see if cannonball is on screen 
			if (sprayerCannonBalls[i]->GetPosition().y < background->getSize().y)
			{
				//draws cannonball
				sprayerCannonBalls[i]->Draw(target);
			}
			//checks if cannonball is still alive
			if (sprayerCannonBalls[i]->GetAlive() == false)
			{
				//clears cannonball memory and deletes it from vector
				delete sprayerCannonBalls[i];
				sprayerCannonBalls[i] = nullptr;
				sprayerCannonBalls.erase(sprayerCannonBalls.begin() + i);

				if (sprayerCannonBalls.size() - 1 > 0)
				{
					i--;
					break;
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

				if (goons.size() - 1 > 0)
				{
					i--;
					break;
				}
			}
			//checks to see if position of goon is off screen
			else if (goons[i]->GetPosition().y >= background->getSize().y)
			{
				if (goons[i] != nullptr)
				{
					//clears goon memory and deletes it from vector
					delete goons[i];
					goons[i] = nullptr;
					goons.erase(goons.begin() + i);

					if (goons.size() - 1 > 0)
					{
						i--;
						break;
					}
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
				delete chargers[i];
				chargers[i] = nullptr;
				chargers.erase(chargers.begin() + i);

				if (chargers.size() - 1 > 0)
				{
					i--;
					break;
				}
			}
			else if (chargers[i]->GetPosition().y >= background->getSize().y)
			{
				if (chargers[i] != nullptr)
				{
					delete chargers[i];
					chargers[i] = nullptr;
					chargers.erase(chargers.begin() + i);

					if (chargers.size() - 1 > 0)
					{
						i--;
						break;
					}
				}
			}
		}
	}
	for (size_t i = 0; i < sprayers.size(); i++)
	{
		if (sprayers[i] != nullptr)
		{
			if (sprayers[i]->GetPosition().y < background->getSize().y)
			{
				sprayers[i]->Draw(target);
			}
			else if (sprayers[i]->GetAlive() == false)
			{
				delete sprayers[i];
				sprayers[i] = nullptr;
				sprayers.erase(sprayers.begin() + i);

				if (sprayers.size() - 1 > 0)
				{
					i--;
					break;
				}
			}
			else if (sprayers[i]->GetPosition().y >= background->getSize().y)
			{
				if (sprayers[i] != nullptr)
				{
					delete sprayers[i];
					sprayers[i] = nullptr;
					sprayers.erase(sprayers.begin() + i);

					if (chargers.size() - 1 > 0)
					{
						i--;
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
	if (player.GetHasAnchor())
	{
		anchorUI.SetOpacity(player.GetHasAnchor());
		anchorUI.Draw(target);
	}
	else
	{
		anchorUI.SetOpacity(player.GetHasAnchor());
		anchorUI.Draw(target);
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

				if (lifePickups.size() - 1 > 0)
				{
					i--;
					break;
				}
				
			}
			else
			{
				lifePickups[i]->Draw(target);
			}
		}
	}
	for (size_t i = 0; i < anchorPickups.size(); i++)
	{
		if (anchorPickups[i] != nullptr)
		{
			if (anchorPickups[i]->GetAlive() == false)
			{
				delete anchorPickups[i];
				anchorPickups[i] = nullptr;
				anchorPickups.erase(anchorPickups.begin() + i);

				if (anchorPickups.size() - 1 > 0)
				{
					i--;
					break;
				}
			}
			else
			{
				anchorPickups[i]->Draw(target);
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
	//plays loss/win state depending on the players alive status
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
			cannonBalls.back()->SetPosition(spriteCaller.GetPosition().x + spriteCaller.GetWidth() / 2, spriteCaller.GetPosition().y);
			break;

		case Projectile::ANCHOR:
			anchors.push_back(new Anchor);
			anchors.back()->SetPosition(spriteCaller.GetPosition().x + spriteCaller.GetWidth() / 2, spriteCaller.GetPosition().y);
			break;

		case Projectile::MULTIFIRE:
			for (size_t i = 0; i < 3; i++)
			{
				cannonBalls.push_back(new CannonBall());
			}
			break;

		case Projectile::GOONCANNONBALL:
			goonCannonBalls.push_back(new CannonBall());
			goonCannonBalls.back()->SetVelocity(0, 400);
			goonCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + goonCannonBalls.back()->GetHeight() / 2);
			break;

		case Projectile::SPRAYERCANNONBALL:
			sprayerCannonBalls.push_back(new CannonBall());
			sprayerCannonBalls.back()->SetVelocity(xVelocity, sprayer.GetVelocity().y);
			sprayerCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x + spriteCaller.GetWidth() / 2, spriteCaller.GetPosition().y + sprayerCannonBalls.back()->GetHeight() / 2);
			xVelocity = -xVelocity;
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
			sprayers.push_back(new Sprayer(this));
			sprayers.back()->SetPosition((float)RandomNumGen((int)xPosMin, (int)xPosMax), 0 - sprayers.back()->GetHeight());
			cooldownClocks[2]->restart();
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
		anchorPickups.push_back(new AnchorPickup());
		anchorPickups.back()->SetPosition(spriteCaller.GetPosition());
		break;
	case PickupType::MULTIFIRE:

		break;
	default:
		break;
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
	timer.ResetTime();
	score.SetPosition((float)background->getSize().x - 300, timer.GetPosition().y + 200);
	score.ResetScore();
	anchorUI.SetPosition(0, 20 + anchorUI.GetHeight() / 2);

	for (size_t i = 0; i < goons.size(); i++)
	{
		delete goons[i];
		goons[i] = nullptr;
		goons.erase(goons.begin() + i);
	}
	for (size_t i = 0; i < chargers.size(); i++)
	{
		delete chargers[i];
		chargers[i] = nullptr;
		chargers.erase(chargers.begin() + i);
	}
	for (size_t i = 0; i < lifePickups.size(); i++)
	{
		delete lifePickups[i];
		lifePickups[i] = nullptr;
		lifePickups.erase(lifePickups.begin() + i);
	}
	for (size_t i = 0; i < anchorPickups.size(); i++)
	{
		delete anchorPickups[i];
		anchorPickups[i] = nullptr;
		anchorPickups.erase(anchorPickups.begin() + i);
	}

	//test vectors
	goons.push_back(new Goon(this));
	goons.back()->SetPosition(background->getSize().x / 2, 0);
	chargers.push_back(new Charger(this, &player));
	chargers.back()->SetPosition(background->getSize().x / 2, 0 - chargers.back()->GetHeight());
	sprayers.push_back(new Sprayer(this));
	sprayers.back()->SetPosition(background->getSize().x / 2, 0);
	//pirateBarricades.push_back(new PirateBarricade(this));
	//pirateBarricades.back()->SetPosition(background->getSize().x / 2 - pirateBarricades.back()->GetWidth() + pirateBarricades.back()->GetWidth(), 0 - pirateBarricades.back()->GetHeight());



	gameRunning = true;
}

