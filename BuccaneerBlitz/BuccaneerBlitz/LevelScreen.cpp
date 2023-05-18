#include "LevelScreen.h"
#include "Player.h"
#include "Game.h"
#include "Timer.h"
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player(newGamePointer->GetWindow(), this)
	, levelStageNumber(2)
	, gameRunning(true)
	, background(newGamePointer->GetWindow())
	, game(newGamePointer)
	, sideBarrierLeft(newGamePointer->GetWindow(), &levelStageNumber)
	, sideBarrierRight(newGamePointer->GetWindow(), &levelStageNumber)
	, bossRoomBarrier(newGamePointer->GetWindow(), &levelStageNumber)
	, cannonBall()
	, anchor()
	, charger(this, &player)
	, goon(this)
	, sprayer(this)
	, pirateBarricade(this, &levelStageNumber)
	, smallIsland(this)
	, cannonBalls()
	, anchors()
	, goonCannonBalls()
	, sprayerCannonBalls()
	, oldCrewMateCannonBalls()
	, pirateBarricades()
	, smallIslands()
	, oldCrewMate(this)
	, pirateLord(newGamePointer->GetWindow(), this, &player)
	, timer(this)
	, score()
	, lifeUI()
	, anchorUI()
	, oldCrewMateLifeUI()
	, pirateLordLifeUI()
	, endPanel(newGamePointer->GetWindow())
	, cooldownClocks()
	, goons()
	, chargers()
	, sprayers()
	, lifePickups()
	, anchorPickups()
	, xVelocity(100)
	, targetColor()
	, currentColor()
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	std::cout << levelStageNumber << std::endl;

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
			cooldownClocks.push_back(new sf::Clock());
			cooldownClocks.push_back(new sf::Clock());

			if (levelStageNumber != 2 && levelStageNumber != 4 && levelStageNumber != 6)
			{
				switch (levelStageNumber)
				{
				case 5:
				{
					if (levelStageNumber == 5)
					{
						//spawn objects on cooldown
						//Sprayers - Clock 2
						if (cooldownClocks[2]->getElapsedTime().asSeconds() > sprayer.GetSpawnTime())
						{
							SpawnEnemy(EnemyType::SPRAYER);
						}
					}
				}
				case 3:
				{
					if (levelStageNumber == 3 || levelStageNumber == 5)
					{
						//chargers - Clock 1
						if (cooldownClocks[1]->getElapsedTime().asSeconds() > charger.GetSpawnTime())
						{
							SpawnEnemy(EnemyType::CHARGER);
						}
					}
				}
				case 1:
				{
					if (levelStageNumber == 1 || levelStageNumber == 3 || levelStageNumber == 5)
					{
						//goons - Clock 0
						if (cooldownClocks[0]->getElapsedTime().asSeconds() > goon.GetSpawnTime())
						{
							SpawnEnemy(EnemyType::GOON);
						}
						//Pirate barricade - Clock 3
						if (cooldownClocks[3]->getElapsedTime().asSeconds() > pirateBarricade.GetSpawnTime())
						{
							SpawnHazard(HazardType::PIRATEBARRICADE);
						}
						//Small Island - Clock 4
						if (cooldownClocks[4]->getElapsedTime().asSeconds() > smallIsland.GetSpawnTime())
						{
							SpawnHazard(HazardType::SMALLISLAND);
						}
					}
				}
				break;
				default:
					break;
				}
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


			if (levelStageNumber == 1 || levelStageNumber == 3 || levelStageNumber == 5)
			{
				//updating
				//
				//

				for (size_t i = goonCannonBalls.size(); i > 0; i--)
				{
					if (goonCannonBalls[i - 1] != nullptr)
					{
						goonCannonBalls[i - 1]->Update(frameTime);
						goonCannonBalls[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = sprayerCannonBalls.size(); i > 0; i--)
				{
					if (sprayerCannonBalls[i - 1] != nullptr)
					{
						sprayerCannonBalls[i - 1]->Update(frameTime);
						sprayerCannonBalls[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = goons.size(); i > 0; i--)
				{
					if (goons[i - 1] != nullptr)
					{
						goons[i -1]->Update(frameTime);
						goons[i -1]->SetColliding(false);
					}
				}

				for (size_t i = chargers.size(); i > 0; i--)
				{
					if (chargers[i -1] != nullptr)
					{
						chargers[i -1]->Update(frameTime);
						chargers[i -1]->SetColliding(false);
					}
				}

				for (size_t i = sprayers.size(); i > 0; i--)
				{
					if (sprayers[i - 1] != nullptr)
					{
						sprayers[i - 1]->Update(frameTime);
						sprayers[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = pirateBarricades.size(); i > 0; i--)
				{
					if (pirateBarricades[i - 1] != nullptr)
					{
						pirateBarricades[i - 1]->Update(frameTime);
						pirateBarricades[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = smallIslands.size(); i > 0; i--)
				{
					if (smallIslands[i - 1] != nullptr)
					{
						smallIslands[i - 1]->Update(frameTime);
						smallIslands[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = lifePickups.size(); i > 0; i--)
				{
					if (lifePickups[i - 1] != nullptr)
					{
						lifePickups[i - 1]->Update(frameTime);
						lifePickups[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = anchorPickups.size(); i > 0; i--)
				{
					if (anchorPickups[i - 1] != nullptr)
					{
						anchorPickups[i - 1]->Update(frameTime);
						anchorPickups[i - 1]->SetColliding(false);
					}
				}

				//Check collisions
				//
				//
			
				for (size_t i = goons.size(); i > 0; i--)
				{
					if (goons[i - 1] != nullptr)
					{
						if (player.CheckColliding(*goons[i - 1]))
						{
							player.SetColliding(true);
							goons[i - 1]->SetColliding(true);
							player.HandleCollision(*goons[i - 1]);
							goons[i - 1]->HandleCollision(player);
						}
					}
				}
				for (size_t i = chargers.size(); i > 0; i--)
				{
					if (chargers[i - 1] != nullptr)
					{
						if (player.CheckColliding(*chargers[i - 1]))
						{
							player.SetColliding(true);
							chargers[i - 1]->SetColliding(true);
							player.HandleCollision(*chargers[i - 1]);
							chargers[i - 1]->HandleCollision(player);
						}
					}
				}
				for (size_t i = lifePickups.size(); i > 0; i--)
				{
					if (lifePickups[i - 1] != nullptr)
					{
						if (player.CheckColliding(*lifePickups[i - 1]))
						{
							player.SetColliding(true);
							lifePickups[i - 1]->SetColliding(true);
							lifePickups[i - 1]->HandleCollision(player);
							if (player.GetLives() >= 3)
							{
								score.AddScore(50);
							}
						}
					}
				}
				for (size_t i = anchorPickups.size(); i > 0; i--)
				{
					if (anchorPickups[i - 1] != nullptr)
					{
						if (player.CheckColliding(*anchorPickups[i - 1]))
						{
							player.SetColliding(true);
							anchorPickups[i - 1]->SetColliding(true);
							player.HandleCollision(*anchorPickups[i - 1]);
							anchorPickups[i - 1]->HandleCollision(player);
							if (player.GetHasAnchor() == true)
							{
								score.AddScore(50);
							}
						}
					}
				}
				for (size_t i = pirateBarricades.size(); i > 0; i--)
				{
					if (pirateBarricades[i - 1] != nullptr)
					{
						if (player.CheckColliding(*pirateBarricades[i - 1]))
						{
							player.SetColliding(true);
							pirateBarricades[i - 1]->SetColliding(true);
							player.HandleCollision(*pirateBarricades[i - 1]);
							pirateBarricades[i - 1]->HandleCollision(player);
						}
					}
				}
				for (size_t i = smallIslands.size(); i > 0; i--)
				{
					if (smallIslands[i - 1] != nullptr)
					{
						if (player.CheckColliding(*smallIslands[i - 1]))
						{
							player.SetColliding(true);
							smallIslands[i - 1]->SetColliding(true);
							player.HandleCollision(*smallIslands[i - 1]);
							smallIslands[i - 1]->HandleCollision(player);
						}
					}
				}

				//cannonballs
				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					for (size_t j = goons.size(); j > 0; j--)
					{
						if (cannonBalls[i - 1] != nullptr && goons[j - 1] != nullptr)
						{
							if (cannonBalls[i - 1]->CheckColliding(*goons[j - 1]))
							{
								score.AddScore(10);
								cannonBalls[i - 1]->SetColliding(true);
								goons[j - 1]->SetColliding(true);
								cannonBalls[i - 1]->HandleCollision(*goons[j - 1]);
								goons[i - 1]->HandleCollision(*cannonBalls[i - 1]);
							}
						}

					}
				}
				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					for (size_t j = chargers.size(); j > 0; j--)
					{
						if (cannonBalls[i - 1] != nullptr && chargers[j - 1] != nullptr)
						{
							if (cannonBalls[i - 1]->CheckColliding(*chargers[j - 1]))
							{
								score.AddScore(20);
								cannonBalls[i - 1]->SetColliding(true);
								chargers[j - 1]->SetColliding(true);
								cannonBalls[i - 1]->HandleCollision(*chargers[j - 1]);
								chargers[i - 1]->HandleCollision(*cannonBalls[i - 1]);
							}
						}
					}
				}
				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					for (size_t j = sprayers.size(); j > 0; j--)
					{
						if (cannonBalls[i - 1] != nullptr && sprayers[j - 1] != nullptr)
						{
							if (cannonBalls[i - 1]->CheckColliding(*sprayers[j - 1]))
							{
								score.AddScore(15);
								cannonBalls[i - 1]->SetColliding(true);
								sprayers[j - 1]->SetColliding(true);
								cannonBalls[i - 1]->HandleCollision(*sprayers[j - 1]);
								sprayers[i - 1]->HandleCollision(*cannonBalls[i - 1]);
							}
						}
					}
				}

				//enemy cannonballs
				for (size_t i = goonCannonBalls.size(); i > 0; i--)
				{
					if (goonCannonBalls[i - 1]->CheckColliding(player))
					{
						goonCannonBalls[i - 1]->SetColliding(true);
						player.SetColliding(true);
						goonCannonBalls[i - 1]->HandleCollision(player);
					}
				}
				for (size_t i = sprayerCannonBalls.size(); i > 0; i--)
				{
					if (sprayerCannonBalls[i - 1]->CheckColliding(player))
					{
						sprayerCannonBalls[i - 1]->SetColliding(true);
						player.SetColliding(true);
						sprayerCannonBalls[i - 1]->HandleCollision(player);
					}
				}

				//anchor
				for (size_t i = anchors.size(); i > 0; i--)
				{
					for (size_t j = pirateBarricades.size(); j > 0; j--)
					{
						if (anchors[i - 1]->CheckColliding(*pirateBarricades[j - 1]))
						{
							score.AddScore(50);
							anchors[i - 1]->SetColliding(true);
							pirateBarricades[j - 1]->SetColliding(true);
							anchors[i - 1]->HandleCollision(*pirateBarricades[j - 1]);
							pirateBarricades[j - 1]->HandleCollision(*anchors[i - 1]);
						}
					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					for (size_t j = goons.size(); j > 0; j--)
					{
						if (anchors[i - 1] != nullptr && goons[j - 1] != nullptr)
						{
							if (anchors[i - 1]->CheckColliding(*goons[j - 1]))
							{
								score.AddScore(10);
								anchors[i - 1]->SetColliding(true);
								goons[j - 1]->SetColliding(true);
								anchors[i - 1]->HandleCollision(*goons[j - 1]);
								goons[i - 1]->HandleCollision(*anchors[i - 1]);
							}
						}

					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					for (size_t j = chargers.size(); j > 0; j--)
					{
						if (anchors[i - 1] != nullptr && chargers[j - 1] != nullptr)
						{
							if (anchors[i - 1]->CheckColliding(*chargers[j - 1]))
							{
								score.AddScore(20);
								anchors[i - 1]->SetColliding(true);
								chargers[j - 1]->SetColliding(true);
								anchors[i - 1]->HandleCollision(*chargers[j - 1]);
								chargers[i - 1]->HandleCollision(*anchors[i - 1]);
							}
						}
					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					for (size_t j = sprayers.size(); j > 0; j--)
					{
						if (anchors[i - 1] != nullptr && sprayers[j - 1] != nullptr)
						{
							if (anchors[i - 1]->CheckColliding(*sprayers[j - 1]))
							{
								score.AddScore(15);
								anchors[i - 1]->SetColliding(true);
								sprayers[j - 1]->SetColliding(true);
								anchors[i - 1]->HandleCollision(*sprayers[j - 1]);
								sprayers[i - 1]->HandleCollision(*anchors[i - 1]);
							}
						}
					}
				}
			}
			else if (levelStageNumber == 2)
			{
				//updating
				//
				//

				oldCrewMate.Update(frameTime);
				oldCrewMate.SetColliding(false);

				//Check collisions
				//
				//

				for (size_t i = oldCrewMateCannonBalls.size(); i > 0; i--)
				{
					if (oldCrewMateCannonBalls[i - 1] != nullptr)
					{
						oldCrewMateCannonBalls[i - 1]->Update(frameTime);
						oldCrewMateCannonBalls[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					if (cannonBalls[i - 1] != nullptr)
					{
						if (cannonBalls[i - 1]->CheckColliding(oldCrewMate))
						{
							cannonBalls[i - 1]->SetColliding(true);
							oldCrewMate.SetColliding(true);
							cannonBalls[i - 1]->HandleCollision(oldCrewMate);
							if (oldCrewMate.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < oldCrewMate.GetBonusTime())
								{
									score.AddScore(100);
								}
								score.AddScore(100);
								timer.ResetTime();
								levelStageNumber++;
							}
						}
					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					if (anchors[i - 1] != nullptr)
					{
						if (anchors[i - 1]->CheckColliding(oldCrewMate))
						{
							anchors[i - 1]->SetColliding(true);
							oldCrewMate.SetColliding(true);
							anchors[i - 1]->HandleCollision(oldCrewMate);
							if (oldCrewMate.GetLives() <= 0)
							{
								score.AddScore(100);
								timer.ResetTime();
								levelStageNumber++;
							}
						}
					}
				}

				for (size_t i = oldCrewMateCannonBalls.size(); i > 0; i--)
				{
					if (oldCrewMateCannonBalls[i - 1]->CheckColliding(player))
					{
						oldCrewMateCannonBalls[i - 1]->SetColliding(true);
						player.SetColliding(true);
						oldCrewMateCannonBalls[i - 1]->HandleCollision(player);
					}
				}

			}
			else if (levelStageNumber == 4)
			{
				//updating
				//
				//

				pirateLord.Update(frameTime);
				pirateLord.SetColliding(false);

				if (pirateLord.CheckColliding(player))
				{
					player.SetColliding(true);
					pirateLord.SetColliding(true);
					pirateLord.HandleCollision(player);
				}

				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					if (cannonBalls[i - 1] != nullptr)
					{
						if (cannonBalls[i - 1]->CheckColliding(pirateLord))
						{
							cannonBalls[i - 1]->SetColliding(true);
							pirateLord.SetColliding(true);
							cannonBalls[i - 1]->HandleCollision(pirateLord);
							if (pirateLord.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < pirateLord.GetBonusTime())
								{
									score.AddScore(200);
								}
								score.AddScore(500);
								timer.ResetTime();
								levelStageNumber++;
							}
						}
					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					if (anchors[i - 1] != nullptr)
					{
						if (anchors[i - 1]->CheckColliding(pirateLord))
						{
							anchors[i - 1]->SetColliding(true);
							pirateLord.SetColliding(true);
							anchors[i - 1]->HandleCollision(pirateLord);
							if (pirateLord.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < pirateLord.GetBonusTime())
								{
									score.AddScore(200);
								}
								score.AddScore(500);
								timer.ResetTime();
								levelStageNumber++;
							}
						}
					}
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
			if (sideBarrierLeft.CheckColliding(oldCrewMate))
			{
				oldCrewMate.SetColliding(true);
				sideBarrierLeft.SetColliding(true);
				oldCrewMate.HandleCollision(sideBarrierLeft);
				sideBarrierLeft.HandleCollision(oldCrewMate);
			}
			if (sideBarrierRight.CheckColliding(oldCrewMate))
			{
				oldCrewMate.SetColliding(true);
				sideBarrierRight.SetColliding(true);
				oldCrewMate.HandleCollision(sideBarrierRight);
				sideBarrierRight.HandleCollision(oldCrewMate);
			}
			for (size_t i = goons.size(); i > 0; i--)
			{
				if (sideBarrierRight.CheckColliding(*goons[i - 1]))
				{
					goons[i - 1]->SetAlive(false);
					goons[i - 1]->HandleCollision(sideBarrierRight);
					sideBarrierRight.HandleCollision(*goons[i - 1]);
				}
				if (sideBarrierLeft.CheckColliding(*goons[i - 1]))
				{
					goons[i - 1]->SetAlive(false);
					goons[i - 1]->HandleCollision(sideBarrierLeft);
					sideBarrierLeft.HandleCollision(*goons[i - 1]);
				}
			}
			for (size_t i = sprayers.size(); i > 0; i--)
			{
				if (sideBarrierRight.CheckColliding(*sprayers[i - 1]))
				{
					sprayers[i - 1]->SetAlive(false);
					sprayers[i - 1]->HandleCollision(sideBarrierRight);
					sideBarrierRight.HandleCollision(*sprayers[i - 1]);
				}
				if (sideBarrierLeft.CheckColliding(*sprayers[i - 1]))
				{
					sprayers[i - 1]->SetAlive(false);
					sprayers[i - 1]->HandleCollision(sideBarrierLeft);
					sideBarrierLeft.HandleCollision(*sprayers[i - 1]);
				}
			}
			for (size_t i = sprayerCannonBalls.size(); i > 0; i--)
			{
				if (sprayerCannonBalls[i - 1]->CheckColliding(sideBarrierLeft))
				{
					sprayerCannonBalls[i - 1]->SetColliding(true);
					sideBarrierLeft.SetColliding(true);
					sprayerCannonBalls[i - 1]->HandleCollision(sideBarrierLeft);
				}
				if (sprayerCannonBalls[i - 1]->CheckColliding(sideBarrierRight))
				{
					sprayerCannonBalls[i - 1]->SetColliding(true);
					sideBarrierRight.SetColliding(true);
					sprayerCannonBalls[i - 1]->HandleCollision(sideBarrierRight);
				}
			}
			for (size_t i = smallIslands.size(); i > 0; i--)
			{
				if (sideBarrierRight.CheckColliding(*smallIslands[i - 1]))
				{
					smallIslands[i - 1]->SetAlive(false);
					smallIslands[i - 1]->HandleCollision(sideBarrierRight);
					sideBarrierRight.HandleCollision(*smallIslands[i - 1]);
				}
				if (sideBarrierLeft.CheckColliding(*smallIslands[i - 1]))
				{
					smallIslands[i - 1]->SetAlive(false);
					smallIslands[i - 1]->HandleCollision(sideBarrierLeft);
					sideBarrierLeft.HandleCollision(*smallIslands[i - 1]);
				}
			}

			//bossroom barrier
			if (levelStageNumber == 2 || levelStageNumber == 4 || levelStageNumber == 6)
			{
				if (bossRoomBarrier.CheckColliding(player))
				{
					player.SetColliding(true);
					bossRoomBarrier.SetColliding(true);
					player.HandleCollision(bossRoomBarrier);
					bossRoomBarrier.HandleCollision(player);

				}
				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					if (cannonBalls[i - 1]->CheckColliding(bossRoomBarrier))
					{
						cannonBalls[i - 1]->SetColliding(true);
						bossRoomBarrier.SetColliding(true);
						cannonBalls[i - 1]->HandleCollision(bossRoomBarrier);
					}
				}
			}
		}
	}
	//when game is not running i.e. win/loss state
	else
	{
		endPanel.Update(frameTime);
		if (score.GetScore() > score.LoadHighScore())
		{
			score.SaveHighScore(score.GetScore());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			game->ChangeGameState(GameState::TITLESCREEN);
		}
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	if (levelStageNumber == 1 || levelStageNumber == 3 || levelStageNumber == 5)
	{
		//set scale of player to match size of current level
		player.SetSpriteScale(1.0f, 1.0f);
		player.SetCollisionOffest(-128, -128);
		for (size_t i = cannonBalls.size(); i > 0; i--)
		{
			cannonBalls[i - 1]->SetSpriteScale(0.25f, 0.25f);
		}

		sideBarrierLeft.Draw(target);
		sideBarrierLeft.UpdateSpriteAsset(levelStageNumber);
		sideBarrierRight.Draw(target);
		sideBarrierRight.UpdateSpriteAsset(levelStageNumber);

		for (size_t i = lifePickups.size(); i > 0; i--)
		{
			if (lifePickups[i - 1] != nullptr)
			{
				if (lifePickups[i - 1]->GetAlive() == false)
				{
					delete lifePickups[i - 1];
					lifePickups[i - 1] = nullptr;
					lifePickups.erase(lifePickups.begin() + (i - 1));
				}
				else
				{
					lifePickups[i -1]->Draw(target);
				}
			}
		}
		for (size_t i = anchorPickups.size(); i > 0; i--)
		{
			if (anchorPickups[i - 1] != nullptr)
			{
				if (anchorPickups[i - 1]->GetAlive() == false)
				{
					delete anchorPickups[i - 1];
					anchorPickups[i - 1] = nullptr;
					anchorPickups.erase(anchorPickups.begin() + (i - 1));
				}
				else
				{
					anchorPickups[i - 1]->Draw(target);
				}
			}
		}

		//pirate barricade
		for (size_t i = pirateBarricades.size(); i > 0; i--)
		{
			if (pirateBarricades[i - 1] != nullptr)
			{
				if (pirateBarricades[i - 1]->GetPosition().y < background->getSize().y)
				{
					pirateBarricades[i - 1]->Draw(target);
				}
				else if (pirateBarricades[i - 1]->GetAlive() == false)
				{
					delete pirateBarricades[i - 1];
					pirateBarricades[i - 1] = nullptr;
					pirateBarricades.erase(pirateBarricades.begin() + (i - 1));
				}
				else if (pirateBarricades[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (pirateBarricades[i - 1] != nullptr)
					{
						pirateBarricades[i - 1] = nullptr;
						delete pirateBarricades[i - 1];
						pirateBarricades.erase(pirateBarricades.begin() + (i - 1));
					}
				}
			}
		}

		//small islands
		for (size_t i = smallIslands.size(); i > 0; i--)
		{
			if (smallIslands[i - 1] != nullptr)
			{
				if (smallIslands[i - 1]->GetPosition().y < background->getSize().y)
				{
					smallIslands[i - 1]->Draw(target);
				}
				else if (smallIslands[i - 1]->GetAlive() == false)
				{
					delete smallIslands[i - 1];
					smallIslands[i - 1] = nullptr;
					smallIslands.erase(smallIslands.begin() + (i - 1));
				}
				else if (smallIslands[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (smallIslands[i - 1] != nullptr)
					{
						smallIslands[i - 1] = nullptr;
						delete smallIslands[i - 1];
						smallIslands.erase(smallIslands.begin() + (i - 1));
					}
				}
			}
		}

		//goon cannonballs
		for (size_t i = goonCannonBalls.size(); i > 0; i--)
		{
			if (goonCannonBalls[i - 1] != nullptr)
			{
				//checks to see if cannonball is on screen 
				if (goonCannonBalls[i - 1]->GetPosition().y < background->getSize().y)
				{
					//draws cannonball
					goonCannonBalls[i - 1]->Draw(target);
				}
				//checks if cannonball is still alive
				if (goonCannonBalls[i - 1]->GetAlive() == false)
				{
					//clears cannonball memory and deletes it from vector
					delete goonCannonBalls[i - 1];
					goonCannonBalls[i - 1] = nullptr;
					goonCannonBalls.erase(goonCannonBalls.begin() + (i - 1));
				}
				//checks to see if position of cannonball is off screen
				else if (goonCannonBalls[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (goonCannonBalls[i - 1] != nullptr)
					{
						//clears cannonball memory and deletes it from vector
						delete goonCannonBalls[i - 1];
						goonCannonBalls[i - 1] = nullptr;
						goonCannonBalls.erase(goonCannonBalls.begin() + (i - 1));
					}
				}
			}
		}

		//sprayer cannonballs
		for (size_t i = sprayerCannonBalls.size(); i > 0; i--)
		{
			if (sprayerCannonBalls[i - 1] != nullptr)
			{
				//checks to see if cannonball is on screen 
				if (sprayerCannonBalls[i - 1]->GetPosition().y < background->getSize().y)
				{
					//draws cannonball
					sprayerCannonBalls[i - 1]->Draw(target);
				}
				//checks if cannonball is still alive
				if (sprayerCannonBalls[i - 1]->GetAlive() == false)
				{
					//clears cannonball memory and deletes it from vector
					delete sprayerCannonBalls[i - 1];
					sprayerCannonBalls[i - 1] = nullptr;
					sprayerCannonBalls.erase(sprayerCannonBalls.begin() + (i - 1));
				}
			}
		}

		//sprayers
		for (size_t i = sprayers.size(); i > 0; i--)
		{
			if (sprayers[i - 1] != nullptr)
			{
				if (sprayers[i - 1]->GetPosition().y < background->getSize().y)
				{
					sprayers[i - 1]->Draw(target);
				}
				else if (sprayers[i - 1]->GetAlive() == false)
				{
					delete sprayers[i - 1];
					sprayers[i - 1] = nullptr;
					sprayers.erase(sprayers.begin() + (i - 1));
				}
				else if (sprayers[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (sprayers[i - 1] != nullptr)
					{
						delete sprayers[i - 1];
						sprayers[i - 1] = nullptr;
						sprayers.erase(sprayers.begin() + (i - 1));
					}
				}
			}
		}

		//goons
		for (size_t i = goons.size(); i > 0; i--)
		{
			if (goons[i - 1] != nullptr)
			{
				//checks to see if goon is on screen 
				if (goons[i - 1]->GetPosition().y < background->getSize().y)
				{
					//draws goon
					goons[i - 1]->Draw(target);
				}
				//checks if goon is still alive
				if (!goons[i - 1]->GetAlive())
				{
					//clears goon memory and deletes it from vector
					delete goons[i - 1];
					goons[i - 1] = nullptr;
					goons.erase(goons.begin() + (i - 1));
				}
				//checks to see if position of goon is off screen
				else if (goons[i - 1]->GetPosition().y >= background->getSize().y)
				{
					//clears goon memory and deletes it from vector
					delete goons[i - 1];
					goons[i - 1] = nullptr;
					goons.erase(goons.begin() + (i - 1));
				}
			}
		}

		//chargers
		for (size_t i = chargers.size(); i > 0; i--)
		{
			if (chargers[i - 1] != nullptr)
			{
				//checks to see if chargers is on screen 
				if (chargers[i - 1]->GetPosition().y < background->getSize().y)
				{
					//draws charger
					chargers[i - 1]->Draw(target);
				}
				//checks if charger is still alive
				else if (chargers[i - 1]->GetAlive() == false)
				{
					//clears charger memory and deletes it from vector
					delete chargers[i - 1];
					chargers[i - 1] = nullptr;
					chargers.erase(chargers.begin() + (i - 1));
				}
				//checks to see if position of charger is off screen
				else if (chargers[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (chargers[i - 1] != nullptr)
					{
						//clears charger memory and deletes it from vector
						delete chargers[i - 1];
						chargers[i - 1] = nullptr;
						chargers.erase(chargers.begin() + (i - 1));
					}
				}
			}
		}
	}
	else if (levelStageNumber == 2)
	{
		player.SetSpriteScale(0.5f, 0.5f);
		player.SetCollisionOffest(-64, -64);
		for (size_t i = cannonBalls.size(); i > 0; i--)
		{
			cannonBalls[i - 1]->SetSpriteScale(0.125f, 0.125f);
		}
		
		bossRoomBarrier.UpdateSpriteAsset(levelStageNumber);
		bossRoomBarrier.Draw(target);
		oldCrewMate.Draw(target);

		for (size_t i = oldCrewMate.GetLives(); i > 0; i--)
		{
			oldCrewMateLifeUI.SetSpriteScale(0.25f, 0.25f);
			oldCrewMateLifeUI.Draw(target);
			oldCrewMateLifeUI.SetPosition(background->getSize().x / 2 + ((i - 1) * oldCrewMateLifeUI.GetWidth() / 4) - oldCrewMate.GetLives() / 2 * oldCrewMateLifeUI.GetWidth() / 4, 10);
		}
		//oldcrewamte cannonballs
		for (size_t i = oldCrewMateCannonBalls.size(); i > 0; i--)
		{
			if (oldCrewMateCannonBalls[i - 1] != nullptr)
			{
				//checks to see if cannonball is on screen 
				if (oldCrewMateCannonBalls[i - 1]->GetPosition().y > 0)
				{
					//draws cannonball
					oldCrewMateCannonBalls[i - 1]->Draw(target);
				}
				//checks if cannonball is still alive
				if (oldCrewMateCannonBalls[i - 1]->GetAlive() == false)
				{
					//clears cannonball memory and deletes it from vector 
					delete oldCrewMateCannonBalls[i - 1];
					oldCrewMateCannonBalls[i - 1] = nullptr;
					oldCrewMateCannonBalls.erase(oldCrewMateCannonBalls.begin() + (i - 1));

				}
				//checks to see if position of cannonball is off screen
				else if (oldCrewMateCannonBalls[i - 1]->GetPosition().y <= 0)
				{
					if (oldCrewMateCannonBalls[i - 1] != nullptr)
					{
						//clears cannonball memory and deletes it from vector
						delete oldCrewMateCannonBalls[i - 1];
						oldCrewMateCannonBalls[i - 1] = nullptr;
						oldCrewMateCannonBalls.erase(oldCrewMateCannonBalls.begin() + (i - 1));
					}
				}
			}

		}
	}
	else if (levelStageNumber == 4)
	{
		player.SetSpriteScale(0.5f, 0.5f);
		player.SetCollisionOffest(-64, -64);
		for (size_t i = cannonBalls.size(); i > 0; i--)
		{
			cannonBalls[i - 1]->SetSpriteScale(0.125f, 0.125f);
		}

		bossRoomBarrier.UpdateSpriteAsset(levelStageNumber);
		bossRoomBarrier.Draw(target);
		pirateLord.Draw(target);

		for (size_t i = pirateLord.GetLives(); i > 0; i--)
		{
			pirateLordLifeUI.SetSpriteScale(0.25f, 0.25f);
			pirateLordLifeUI.Draw(target);
			pirateLordLifeUI.SetPosition(background->getSize().x / 2 + ((i - 1) * pirateLordLifeUI.GetWidth() / 4) - pirateLord.GetLives() / 2 * pirateLordLifeUI.GetWidth() / 4, 10);
		}
	}
	else if (levelStageNumber == 6)
	{
		player.SetSpriteScale(0.5f, 0.5f);
		player.SetCollisionOffest(-64, -64);
		for (size_t i = cannonBalls.size(); i > 0; i--)
		{
			cannonBalls[i - 1]->SetSpriteScale(0.125f, 0.125f);
		}

		bossRoomBarrier.UpdateSpriteAsset(levelStageNumber);
		bossRoomBarrier.Draw(target);
	}

	//cannonballs
	for (size_t i = cannonBalls.size(); i > 0; i--)
	{
		if (cannonBalls[i - 1] != nullptr)
		{
			//checks to see if cannonball is on screen 
			if (cannonBalls[i - 1]->GetPosition().y > 0)
			{
				//draws cannonball
				cannonBalls[i - 1]->Draw(target);
			}
			//checks if cannonball is still alive
			if (cannonBalls[i - 1]->GetAlive() == false)
			{
				//clears cannonball memory and deletes it from vector 
				delete cannonBalls[i - 1];
				cannonBalls[i - 1] = nullptr;
				cannonBalls.erase(cannonBalls.begin() + (i - 1));
			}

			//checks to see if position of cannonball is off screen
			else if (cannonBalls[i - 1]->GetPosition().y <= 0)
			{
				if (cannonBalls[i - 1] != nullptr)
				{
					//clears cannonball memory and deletes it from vector
					delete cannonBalls[i - 1];
					cannonBalls[i - 1] = nullptr;
					cannonBalls.erase(cannonBalls.begin() + (i - 1));
				}
			}
		}
	}
	

	//anchors
	for (size_t i = anchors.size(); i > 0; i--)
	{
		if (anchors[i - 1] != nullptr)
		{
			//checks to see if cannonball is on screen 
			if (anchors[i - 1]->GetPosition().y > 0)
			{
				//draws cannonball
				anchors[i - 1]->Draw(target);
			}
			//checks if cannonball is still alive
			if (anchors[i - 1]->GetAlive() == false)
			{
				//clears cannonball memory and deletes it from vector 
				delete anchors[i - 1];
				anchors[i - 1] = nullptr;
				anchors.erase(anchors.begin() + (i - 1));
			}
			//checks to see if position of cannonball is off screen
			else if (anchors[i - 1]->GetPosition().y <= 0)
			{
				if (anchors[i - 1] != nullptr)
				{
					//clears cannonball memory and deletes it from vector
					delete anchors[i - 1];
					anchors[i - 1] = nullptr;
					anchors.erase(anchors.begin() + (i - 1));
				}
			}
		}

	}

	player.Draw(target);
	timer.Draw(target);
	score.Draw(target);
	for (size_t i = player.GetLives(); i > 0; i--)
	{
		lifeUI.Draw(target);
		lifeUI.SetPosition(0 + ((i - 1) * lifeUI.GetWidth() / 2), 10);
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
		targetColor = sf::Color(38, 73, 202, 255);
	}
	else if (currentLevel == 3 || currentLevel == 4) 
	{
		targetColor = sf::Color(80, 104, 63, 255);
	}
	else if (currentLevel == 5 || currentLevel == 6)
	{
		targetColor = sf::Color(7, 9, 22, 255);
	}
	else
	{
		//error...
	}

	//set the background color
	background->clear(targetColor);
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
			cannonBalls.back()->SetPosition(spriteCaller.GetPosition().x - cannonBall.GetWidth() / 8, spriteCaller.GetPosition().y - spriteCaller.GetHeight() / 2);
			break;

		case Projectile::ANCHOR:
			anchors.push_back(new Anchor);
			anchors.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y - spriteCaller.GetHeight() / 2);
			break;

		case Projectile::MULTIFIRE:
			for (size_t i = 0; i < 3; ++i)
			{
				cannonBalls.push_back(new CannonBall());
				cannonBalls.back()->SetVelocity(60 - i * 20, cannonBall.GetVelocity().y);
				cannonBalls.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + cannonBall.GetHeight() / 2);
			}
			break;

		case Projectile::GOONCANNONBALL:
			goonCannonBalls.push_back(new CannonBall());
			goonCannonBalls.back()->SetVelocity(0, 400);
			goonCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + cannonBall.GetHeight() / 2);
			break;

		case Projectile::SPRAYERCANNONBALL:
			sprayerCannonBalls.push_back(new CannonBall());
			sprayerCannonBalls.back()->SetVelocity(xVelocity, sprayer.GetVelocity().y);
			sprayerCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x + spriteCaller.GetWidth() / 2, spriteCaller.GetPosition().y + cannonBall.GetHeight() / 2);
			xVelocity = -xVelocity;
			break;

		case Projectile::OLDCREWMATECANNONBALLS:
			for (size_t i = 0; i < 5; ++i)
			{
				oldCrewMateCannonBalls.push_back(new CannonBall());
				oldCrewMateCannonBalls.back()->SetVelocity(100 - i * 20, 400);
				oldCrewMateCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + cannonBall.GetHeight() / 2);
			}
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
			goons.back()->SetPosition((float)RandomNumGen((int)xPosMin, (int)xPosMax), 0 - goon.GetHeight());
			cooldownClocks[0]->restart();
		break;

	case EnemyType::CHARGER:
			chargers.push_back(new Charger(this, &player));
			chargers.back()->SetPosition(background->getSize().x / 2, 0 - charger.GetHeight());
			cooldownClocks[1]->restart();
		break;

	case EnemyType::SPRAYER:
			sprayers.push_back(new Sprayer(this));
			sprayers.back()->SetPosition((float)RandomNumGen((int)xPosMin, (int)xPosMax), 0 - sprayer.GetHeight());
			cooldownClocks[2]->restart();
		break;

	default:
		break;
	}
}

void LevelScreen::SpawnHazard(HazardType hazardType)
{
	//limits of level space
	float xPosMin = 0 + sideBarrierLeft.GetWidth() / 2;
	float xPosMax = background->getSize().x - sideBarrierRight.GetWidth() / 2;

	switch (hazardType)
	{
	case HazardType::PIRATEBARRICADE:
		pirateBarricades.push_back(new PirateBarricade(this, &levelStageNumber));
		pirateBarricades.back()->SetPosition(background->getSize().x / 2 - pirateBarricade.GetWidth() / 2 - 250, 0 - pirateBarricade.GetHeight());
		cooldownClocks[3]->restart();
		break;
	case HazardType::SMALLISLAND:
		smallIslands.push_back(new SmallIsland(this));
		smallIslands.back()->SetPosition((float)RandomNumGen((int)xPosMin, (int)xPosMax), 0 - smallIsland.GetHeight());
		cooldownClocks[4]->restart();
		break;
	default:
		break;
	}
}

void LevelScreen::SpawnPickUp(PickupType pickupType, sf::Vector2f position)
{
	switch (pickupType)
	{
	case PickupType::LIFE:
		lifePickups.push_back(new LifePickup());
		lifePickups.back()->SetPosition(position);
		break;
	case PickupType::ANCHOR:
		anchorPickups.push_back(new AnchorPickup());
		anchorPickups.back()->SetPosition(position);
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

void LevelScreen::Restart()
{
	sideBarrierLeft.ResetPosition("left");
	sideBarrierRight.ResetPosition("right");
	player.SetPosition(background->getSize().x / 2 - player.GetWidth() / 2, 800);
	timer.SetPosition((float)background->getSize().x - 300, 10);
	timer.ResetTime();
	score.SetPosition((float)background->getSize().x - 300, timer.GetPosition().y + 50);
	score.ResetScore();
	anchorUI.SetPosition(0, 20 + anchorUI.GetHeight() / 2);
	oldCrewMate.SetPosition(350, 300);
	pirateLord.SetPosition(350, 300);

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
	for (size_t i = 0; i < sprayers.size(); i++)
	{
		delete sprayers[i];
		sprayers[i] = nullptr;
		sprayers.erase(sprayers.begin() + i);
	}
	for (size_t i = 0; i < pirateBarricades.size(); i++)
	{
		delete pirateBarricades[i];
		pirateBarricades[i] = nullptr;
		pirateBarricades.erase(pirateBarricades.begin() + i);
	}
	for (size_t i = 0; i < smallIslands.size(); i++)
	{
		delete smallIslands[i];
		smallIslands[i] = nullptr;
		smallIslands.erase(smallIslands.begin() + i);
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

	gameRunning = true;
}

