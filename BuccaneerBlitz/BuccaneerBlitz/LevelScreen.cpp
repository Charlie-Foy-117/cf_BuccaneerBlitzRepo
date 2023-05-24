#include "LevelScreen.h"
#include "Player.h"
#include "Game.h"
#include "Timer.h"
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player(newGamePointer->GetWindow(), this)
	, levelStageNumber(3)
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
	, tentacle(this)
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
	, kraken(this)
	, tentacles()
	, timer(this)
	, score()
	, lifeUI()
	, anchorUI()
	, multiFireUI()
	, oldCrewMateLifeUI()
	, pirateLordLifeUI()
	, krakenLifeUI()
	, endPanel(newGamePointer->GetWindow())
	, cooldownClocks()
	, goons()
	, chargers()
	, sprayers()
	, lifePickups()
	, anchorPickups()
	, multiFirePickups()
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
		if (kraken.GetAlive() == false)
		{
			gameRunning = false;
			TriggerEndState();
		}
		if (player.GetAlive() != true)
		{
			gameRunning = false;
			TriggerEndState();
		}
		else
		{
			//cooldown clocks
			for (size_t i = 0; i < 6; i++)
			{
				cooldownClocks.push_back(new sf::Clock());
			}
			//Cooldown clocks
			//clock 0 = goons
			//clock 1 = chargers
			//clock 2 = sprayers
			//clcok 3 = piratebarricades
			//clock 4 = smallislands
			//clock 5 = Tentacles

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
			else if (levelStageNumber == 6)
			{
				//Tentacle - Clock 5
				if (cooldownClocks[5]->getElapsedTime().asSeconds() > tentacle.GetSpawnTime())
				{
					SpawnEnemy(EnemyType::TENTACLE);
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

				for (size_t i = multiFirePickups.size(); i > 0; i--)
				{
					if (multiFirePickups[i - 1] != nullptr)
					{
						multiFirePickups[i - 1]->Update(frameTime);
						multiFirePickups[i - 1]->SetColliding(false);
					}
				}

				//Check collisions
				//
				//
			
				for (size_t i = goons.size(); i > 0; i--)
				{
					if (goons[i - 1] != nullptr)
					{
						//checks to see if goon is collding with player
						if (player.CheckColliding(*goons[i - 1]))
						{
							//set goon and player to colling = true
							player.SetColliding(true);
							goons[i - 1]->SetColliding(true);
							//handle collisions between each object
							player.HandleCollision(*goons[i - 1]);
							goons[i - 1]->HandleCollision(player);
						}
					}
				}
				for (size_t i = chargers.size(); i > 0; i--)
				{
					if (chargers[i - 1] != nullptr)
					{
						//checks to see if charger is collding with player
						if (player.CheckColliding(*chargers[i - 1]))
						{
							//set charger and player to colling = true
							player.SetColliding(true);
							chargers[i - 1]->SetColliding(true);
							//handle collisions between each object
							player.HandleCollision(*chargers[i - 1]);
							chargers[i - 1]->HandleCollision(player);
						}
					}
				}
				for (size_t i = sprayers.size(); i > 0; i--)
				{
					if (sprayers[i - 1] != nullptr)
					{
						// checks to see if sprayer is collding with player
						if (player.CheckColliding(*sprayers[i - 1]))
						{
							//set sprayer and player to colling = true
							player.SetColliding(true);
							sprayers[i - 1]->SetColliding(true);
							//handle collisions between each object
							player.HandleCollision(*sprayers[i - 1]);
							sprayers[i - 1]->HandleCollision(player);
						}
					}
				}
				for (size_t i = lifePickups.size(); i > 0; i--)
				{
					if (lifePickups[i - 1] != nullptr)
					{
						// checks to see if lifepickup is collding with player
						if (player.CheckColliding(*lifePickups[i - 1]))
						{
							//set lifepickup and player to colling = true
							player.SetColliding(true);
							lifePickups[i - 1]->SetColliding(true);
							//handle collisions between each object
							lifePickups[i - 1]->HandleCollision(player);
							//check lives on the player
							if (player.GetLives() >= 3)
							{
								//add to score
								score.AddScore(50);
							}
						}
					}
				}
				for (size_t i = anchorPickups.size(); i > 0; i--)
				{
					if (anchorPickups[i - 1] != nullptr)
					{
						// checks to see if anchorpickup is collding with player
						if (player.CheckColliding(*anchorPickups[i - 1]))
						{
							//set anchorpickup and player to colling = true
							player.SetColliding(true);
							anchorPickups[i - 1]->SetColliding(true);
							//handle collisions between each object
							player.HandleCollision(*anchorPickups[i - 1]);
							anchorPickups[i - 1]->HandleCollision(player);
							//check anchor status on the player
							if (player.GetHasAnchor() == true)
							{
								//add to score
								score.AddScore(50);
							}
						}
					}
				}
				for (size_t i = multiFirePickups.size(); i > 0; i--)
				{
					if (multiFirePickups[i - 1] != nullptr)
					{
						// checks to see if multifirepickup is collding with player
						if (player.CheckColliding(*multiFirePickups[i - 1]))
						{
							//set multifirepickup and player to colling = true
							player.SetColliding(true);
							multiFirePickups[i - 1]->SetColliding(true);
							//handle collisions between each object
							player.HandleCollision(*multiFirePickups[i - 1]);
							multiFirePickups[i - 1]->HandleCollision(player);
							//check multifire status on the player
							if (player.GetHasMultiFire() == true)
							{
								//add to score
								score.AddScore(50);
							}
						}
					}
				}
				for (size_t i = pirateBarricades.size(); i > 0; i--)
				{
					if (pirateBarricades[i - 1] != nullptr)
					{
						// checks to see if pirate barricade is collding with player
						if (player.CheckColliding(*pirateBarricades[i - 1]))
						{
							//set piratebarricade and player to colling = true
							player.SetColliding(true);
							pirateBarricades[i - 1]->SetColliding(true);
							//handle collisions between each object
							player.HandleCollision(*pirateBarricades[i - 1]);
							pirateBarricades[i - 1]->HandleCollision(player);
						}
					}
				}
				for (size_t i = smallIslands.size(); i > 0; i--)
				{
					if (smallIslands[i - 1] != nullptr)
					{
						// checks to see if smallisland is collding with player
						if (player.CheckColliding(*smallIslands[i - 1]))
						{
							//set smallisland and player to colling = true
							player.SetColliding(true);
							smallIslands[i - 1]->SetColliding(true);
							//handle collisions between each object
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
							// checks to see if goon is collding with cannonball
							if (cannonBalls[i - 1]->CheckColliding(*goons[j - 1]))
							{
								//add to score
								score.AddScore(10);
								//set goon and cannonball to colling = true
								cannonBalls[i - 1]->SetColliding(true);
								goons[j - 1]->SetColliding(true);
								//handle collisions between each object
								cannonBalls[i - 1]->HandleCollision(*goons[j - 1]);
								goons[j - 1]->HandleCollision(*cannonBalls[i - 1]);
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
							// checks to see if charger is collding with cannonball
							if (cannonBalls[i - 1]->CheckColliding(*chargers[j - 1]))
							{
								//add to score
								score.AddScore(20);
								//set charger and cannonball to colling = true
								cannonBalls[i - 1]->SetColliding(true);
								chargers[j - 1]->SetColliding(true);
								//handle collisions between each object
								cannonBalls[i - 1]->HandleCollision(*chargers[j - 1]);
								chargers[j - 1]->HandleCollision(*cannonBalls[i - 1]);
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
							// checks to see if sprayer is collding with cannonball
							if (cannonBalls[i - 1]->CheckColliding(*sprayers[j - 1]))
							{
								//add to score
								score.AddScore(15);
								//set sprayer and cannonball to colling = true
								cannonBalls[i - 1]->SetColliding(true);
								sprayers[j - 1]->SetColliding(true);
								//handle collisions between each object
								cannonBalls[i - 1]->HandleCollision(*sprayers[j - 1]);
								sprayers[j - 1]->HandleCollision(*cannonBalls[i - 1]);
							}
						}
					}
				}

				//enemy cannonballs
				for (size_t i = goonCannonBalls.size(); i > 0; i--)
				{
					// checks to see if player is collding with gooncannonball
					if (goonCannonBalls[i - 1]->CheckColliding(player))
					{
						//set player and gooncannonball to colling = true
						goonCannonBalls[i - 1]->SetColliding(true);
						player.SetColliding(true);
						//handle collisions between each object
						goonCannonBalls[i - 1]->HandleCollision(player);
					}
				}
				for (size_t i = sprayerCannonBalls.size(); i > 0; i--)
				{
					// checks to see if player is collding with sprayercannonball
					if (sprayerCannonBalls[i - 1]->CheckColliding(player))
					{
						//set player and sprayercannonball to colling = true
						sprayerCannonBalls[i - 1]->SetColliding(true);
						player.SetColliding(true);
						//handle collisions between each object
						sprayerCannonBalls[i - 1]->HandleCollision(player);
					}
				}

				//anchor
				for (size_t i = anchors.size(); i > 0; i--)
				{
					for (size_t j = pirateBarricades.size(); j > 0; j--)
					{
						// checks to see if piratebarricade is collding with anchor
						if (anchors[i - 1]->CheckColliding(*pirateBarricades[j - 1]))
						{
							//add to score
							score.AddScore(50);
							//set anchor and piratebarricade to colling = true
							anchors[i - 1]->SetColliding(true);
							pirateBarricades[j - 1]->SetColliding(true);
							//handle collisions between each object
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
							// checks to see if goon is collding with anchor
							if (anchors[i - 1]->CheckColliding(*goons[j - 1]))
							{
								//add to score
								score.AddScore(10);
								//set anchor and goon to colling = true
								anchors[i - 1]->SetColliding(true);
								goons[j - 1]->SetColliding(true);
								//handle collisions between each object
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
							// checks to see if charger is collding with anchor
							if (anchors[i - 1]->CheckColliding(*chargers[j - 1]))
							{
								//add to score
								score.AddScore(20);
								//set anchor and charger to colling = true
								anchors[i - 1]->SetColliding(true);
								chargers[j - 1]->SetColliding(true);
								//handle collisions between each object
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
							// checks to see if sprayer is collding with anchor
							if (anchors[i - 1]->CheckColliding(*sprayers[j - 1]))
							{
								//add to score
								score.AddScore(15);
								//set anchor and sprayer to colling = true
								anchors[i - 1]->SetColliding(true);
								sprayers[j - 1]->SetColliding(true);
								//handle collisions between each object
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

				for (size_t i = oldCrewMateCannonBalls.size(); i > 0; i--)
				{
					if (oldCrewMateCannonBalls[i - 1] != nullptr)
					{
						oldCrewMateCannonBalls[i - 1]->Update(frameTime);
						oldCrewMateCannonBalls[i - 1]->SetColliding(false);
					}
				}

				//Check collisions
				//
				//

				//checks to see if player is collding with oldcrewmate
				if (oldCrewMate.CheckColliding(player))
				{
					//set oldcrewmate and player to colling = true
					player.SetColliding(true);
					oldCrewMate.SetColliding(true);
					//handle collision between each object
					oldCrewMate.HandleCollision(player);
				}

				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					if (cannonBalls[i - 1] != nullptr)
					{
						//checks to see if player is collding with oldcrewmate
						if (cannonBalls[i - 1]->CheckColliding(oldCrewMate))
						{
							//set oldcrewmate and player to colling = true
							cannonBalls[i - 1]->SetColliding(true);
							oldCrewMate.SetColliding(true);
							//handle collision between each object
							cannonBalls[i - 1]->HandleCollision(oldCrewMate);
							//check oldcrewmates lives
							if (oldCrewMate.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < oldCrewMate.GetBonusTime())
								{
									//add to score
									score.AddScore(100);
								}
								//add to score
								score.AddScore(100);
								timer.ResetTime();
								//move up a level
								levelStageNumber++;
							}
						}
					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					if (anchors[i - 1] != nullptr)
					{
						//checks to see if oldcrewmate is collding with anchor
						if (anchors[i - 1]->CheckColliding(oldCrewMate))
						{
							//set oldcrewmate and anchor to colling = true
							anchors[i - 1]->SetColliding(true);
							oldCrewMate.SetColliding(true);
							//handle collision between each object
							anchors[i - 1]->HandleCollision(oldCrewMate);
							//check oldcrewmates lives
							if (oldCrewMate.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < oldCrewMate.GetBonusTime())
								{
									//add to score
									score.AddScore(100);
								}
								//add to score
								score.AddScore(100);
								timer.ResetTime();
								//move up a level
								levelStageNumber++;
							}
						}
					}
				}

				for (size_t i = oldCrewMateCannonBalls.size(); i > 0; i--)
				{
					//checks to see if player is collding with oldcrewmate
					if (oldCrewMateCannonBalls[i - 1]->CheckColliding(player))
					{
						//set oldcrewmate and player to colling = true
						oldCrewMateCannonBalls[i - 1]->SetColliding(true);
						player.SetColliding(true);
						//handle collision between each object
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

				//Check collisions
				//
				//

				//checks to see if player is collding with piratelord
				if (pirateLord.CheckColliding(player))
				{
					//set piratelord and player to colling = true
					player.SetColliding(true);
					pirateLord.SetColliding(true);
					//handle collision between each object
					pirateLord.HandleCollision(player);
				}

				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					if (cannonBalls[i - 1] != nullptr)
					{
						//checks to see if piratelord is collding with cannonball
						if (cannonBalls[i - 1]->CheckColliding(pirateLord))
						{
							//set piratelord and cannonball to colling = true
							cannonBalls[i - 1]->SetColliding(true);
							pirateLord.SetColliding(true);
							//handle collision between each object
							cannonBalls[i - 1]->HandleCollision(pirateLord);
							if (pirateLord.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < pirateLord.GetBonusTime())
								{
									//add to score
									score.AddScore(200);
								}
								//add to score
								score.AddScore(500);
								timer.ResetTime();
								//move up level
								levelStageNumber++;
							}
						}
					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					if (anchors[i - 1] != nullptr)
					{
						//checks to see if oldcrewmate is collding with anchor
						if (anchors[i - 1]->CheckColliding(pirateLord))
						{
							//set piratelord and anchor to colling = true
							anchors[i - 1]->SetColliding(true);
							pirateLord.SetColliding(true);
							//handle collision between each object
							anchors[i - 1]->HandleCollision(pirateLord);
							if (pirateLord.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < pirateLord.GetBonusTime())
								{
									//add to score
									score.AddScore(200);
								}
								//add to score
								score.AddScore(500);
								timer.ResetTime();
								//move up level
								levelStageNumber++;
							}
						}
					}
				}
			}
			else if (levelStageNumber == 6)
			{
				//updating
				//
				//

				kraken.Update(frameTime);
				kraken.SetColliding(false);

				for (size_t i = tentacles.size(); i > 0; i--)
				{
					if (tentacles[i - 1] != nullptr)
					{
						tentacles[i - 1]->Update(frameTime);
						tentacles[i - 1]->SetColliding(false);
					}
				}

				for (size_t i = tentacleProjectiles.size(); i > 0; i--)
				{
					if (tentacleProjectiles[i - 1] != nullptr)
					{
						tentacleProjectiles[i - 1]->Update(frameTime);
						tentacleProjectiles[i - 1]->SetColliding(false);
					}
				}

				//Check collisions
				//
				//

				//checks to see if kraken is collding with player
				if (kraken.CheckColliding(player))
				{
					//set kraken and player to colling = true
					player.SetColliding(true);
					kraken.SetColliding(true);
					//handle collision between each object
					kraken.HandleCollision(player);
				}

				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					for (size_t j = tentacles.size(); j > 0; j--)
					{
						if (cannonBalls[i - 1] != nullptr)
						{
							//checks to see if tentacles is collding with cannonball
							if (cannonBalls[i - 1]->CheckColliding(*tentacles[j - 1]))
							{
								//set tentacles and cannonball to colling = true
								cannonBalls[i - 1]->SetColliding(true);
								tentacles[j - 1]->SetColliding(true);
								//handle collision between each object
								cannonBalls[i - 1]->HandleCollision(*tentacles[j - 1]);
							}
						}
					}
				}

				for (size_t i = tentacleProjectiles.size(); i > 0; i--)
				{
					if (tentacleProjectiles[i - 1] != nullptr)
					{
						//checks to see if tentacleprojectiles is collding with player
						if (tentacleProjectiles[i - 1]->CheckColliding(player))
						{
							//set tentacleprojectiles and player to colling = true
							tentacleProjectiles[i - 1]->SetColliding(true);
							player.SetColliding(true);
							//handle collision between each object
							tentacleProjectiles[i - 1]->HandleCollision(player);
						}
					}
				}

				for (size_t i = cannonBalls.size(); i > 0; i--)
				{
					if (cannonBalls[i - 1] != nullptr)
					{
						//checks to see if kraken is collding with cannonball
						if (cannonBalls[i - 1]->CheckColliding(kraken))
						{
							//set kraken and cannonball to colling = true
							cannonBalls[i - 1]->SetColliding(true);
							kraken.SetColliding(true);
							//handle collision between each object
							cannonBalls[i - 1]->HandleCollision(kraken);
							if (kraken.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < kraken.GetBonusTime())
								{
									//add to score
									score.AddScore(300);
								}
								//add to score
								score.AddScore(1000);
								timer.ResetTime();
							}
						}
					}
				}
				for (size_t i = anchors.size(); i > 0; i--)
				{
					if (anchors[i - 1] != nullptr)
					{
						//checks to see if kraken is collding with anchor
						if (anchors[i - 1]->CheckColliding(kraken))
						{
							//set kraken and anchor to colling = true
							anchors[i - 1]->SetColliding(true);
							kraken.SetColliding(true);
							//handle collision between each object
							anchors[i - 1]->HandleCollision(kraken);
							if (kraken.GetLives() <= 0)
							{
								//checks to see if boss was beaten before the bonus time
								if (timer.GetGameTime().getElapsedTime().asSeconds() < kraken.GetBonusTime())
								{
									//add to score
									score.AddScore(300);
								}
								//add to score
								score.AddScore(1000);
								timer.ResetTime();
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
			if (sideBarrierLeft.CheckColliding(kraken))
			{
				kraken.SetColliding(true);
				sideBarrierLeft.SetColliding(true);
				kraken.HandleCollision(sideBarrierLeft);
				sideBarrierLeft.HandleCollision(kraken);
			}
			if (sideBarrierRight.CheckColliding(kraken))
			{
				kraken.SetColliding(true);
				sideBarrierRight.SetColliding(true);
				kraken.HandleCollision(sideBarrierRight);
				sideBarrierRight.HandleCollision(kraken);
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
			for (size_t i = tentacles.size(); i > 0; i--)
			{
				if (sideBarrierRight.CheckColliding(*tentacles[i - 1]))
				{
					tentacles[i - 1]->HandleCollision(sideBarrierRight);
					sideBarrierRight.HandleCollision(*tentacles[i - 1]);
				}
				if (sideBarrierLeft.CheckColliding(*tentacles[i - 1]))
				{
					tentacles[i - 1]->HandleCollision(sideBarrierLeft);
					sideBarrierLeft.HandleCollision(*tentacles[i - 1]);
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
				//checks to see if lifepickup is on dead 
				if (lifePickups[i - 1]->GetAlive() == false)
				{
					//clears lifepickup memory and deletes it from vector
					delete lifePickups[i - 1];
					lifePickups[i - 1] = nullptr;
					lifePickups.erase(lifePickups.begin() + (i - 1));
				}
				else
				{
					//draws lifepickup
					lifePickups[i -1]->Draw(target);
				}
			}
		}
		for (size_t i = anchorPickups.size(); i > 0; i--)
		{
			if (anchorPickups[i - 1] != nullptr)
			{
				//checks to see if anchorpickup is on dead 
				if (anchorPickups[i - 1]->GetAlive() == false)
				{
					//clears anchorpickup memory and deletes it from vector
					delete anchorPickups[i - 1];
					anchorPickups[i - 1] = nullptr;
					anchorPickups.erase(anchorPickups.begin() + (i - 1));
				}
				else
				{
					//draws anchorpickup
					anchorPickups[i - 1]->Draw(target);
				}
			}
		}
		for (size_t i = multiFirePickups.size(); i > 0; i--)
		{
			if (multiFirePickups[i - 1] != nullptr)
			{
				//checks to see if multifirepickup is on dead 
				if (multiFirePickups[i - 1]->GetAlive() == false)
				{
					//clears multifirepickup memory and deletes it from vector
					delete multiFirePickups[i - 1];
					multiFirePickups[i - 1] = nullptr;
					multiFirePickups.erase(multiFirePickups.begin() + (i - 1));
				}
				else
				{
					//draws multifirepickup
					multiFirePickups[i - 1]->Draw(target);
				}
			}
		}

		//pirate barricade
		for (size_t i = pirateBarricades.size(); i > 0; i--)
		{
			if (pirateBarricades[i - 1] != nullptr)
			{
				//checks to see if piratebarricade is on screen 
				if (pirateBarricades[i - 1]->GetPosition().y < background->getSize().y)
				{
					//draws piratebarricade
					pirateBarricades[i - 1]->Draw(target);
				}
				//checks if piratebarricade is still alive
				else if (pirateBarricades[i - 1]->GetAlive() == false)
				{
					//clears piratebarricade memory and deletes it from vector
					delete pirateBarricades[i - 1];
					pirateBarricades[i - 1] = nullptr;
					pirateBarricades.erase(pirateBarricades.begin() + (i - 1));
				}
				//checks to see if position of piratebarricade is off screen
				else if (pirateBarricades[i - 1]->GetPosition().y >= background->getSize().y)
				{
					//clears piratebarricade memory and deletes it from vector
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
				//checks to see if smallisland is on screen 
				if (smallIslands[i - 1]->GetPosition().y < background->getSize().y)
				{
					//draws smallisland
					smallIslands[i - 1]->Draw(target);
				}
				//checks if smallisland is still alive
				else if (smallIslands[i - 1]->GetAlive() == false)
				{
					//clears smallisland memory and deletes it from vector
					delete smallIslands[i - 1];
					smallIslands[i - 1] = nullptr;
					smallIslands.erase(smallIslands.begin() + (i - 1));
				}
				//checks to see if position of smallisland is off screen
				else if (smallIslands[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (smallIslands[i - 1] != nullptr)
					{
						//clears smallisland memory and deletes it from vector
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
				//checks to see if sprayer is on screen 
				if (sprayers[i - 1]->GetPosition().y < background->getSize().y)
				{
					//draws sprayer
					sprayers[i - 1]->Draw(target);
				}
				//checks if sprayer is still alive
				else if (sprayers[i - 1]->GetAlive() == false)
				{
					//clears sprayer memory and deletes it from vector
					delete sprayers[i - 1];
					sprayers[i - 1] = nullptr;
					sprayers.erase(sprayers.begin() + (i - 1));
				}
				//checks to see if position of sprayer is off screen
				else if (sprayers[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (sprayers[i - 1] != nullptr)
					{
						//clears sprayer memory and deletes it from vector
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
		kraken.Draw(target);

		for (size_t i = tentacles.size(); i > 0; i--)
		{
			if (tentacles[i - 1] != nullptr)
			{
				//checks to see if tentacle is alive 
				if (tentacles[i - 1]->GetAlive())
				{
					//draws tentacle
					tentacles[i - 1]->Draw(target);
				}
				//checks if tentacle is still alive
				else if (tentacles[i - 1]->GetAlive() == false)
				{
					if (tentacles[i - 1] != nullptr)
					{
						//clears tentacle memory and deletes it from vector 
						tentacles[i - 1] = nullptr;
						delete tentacles[i - 1];
						tentacles.erase(tentacles.begin() + (i - 1));
					}
				}
			}
		}

		for (size_t i = tentacleProjectiles.size(); i > 0; i--)
		{
			if (tentacleProjectiles[i - 1] != nullptr)
			{
				//checks to see if tentacleprojectile is alive 
				if (tentacleProjectiles[i - 1]->GetAlive())
				{
					//draws tentacleprojectile
					tentacleProjectiles[i - 1]->Draw(target);
				}
				//checks if tentacleprojectile is still alive
				else if (tentacleProjectiles[i - 1]->GetAlive() == false)
				{
					if (tentacleProjectiles[i - 1] != nullptr)
					{
						//clears tentacleprojectile memory and deletes it from vector 
						tentacleProjectiles[i - 1] = nullptr;
						delete tentacleProjectiles[i - 1];
						tentacleProjectiles.erase(tentacleProjectiles.begin() + (i - 1));
					}
				}
				//checks to see if position of tentacleprojectile is off screen
				else if (tentacleProjectiles[i - 1]->GetPosition().y >= background->getSize().y)
				{
					if (tentacleProjectiles[i - 1] != nullptr)
					{
						//clears tentacleprojectile memory and deletes it from vector
						delete tentacleProjectiles[i - 1];
						tentacleProjectiles[i - 1] = nullptr;
						tentacleProjectiles.erase(tentacleProjectiles.begin() + (i - 1));
					}
				}
			}
		}

		for (size_t i = kraken.GetLives(); i > 0; i--)
		{
			krakenLifeUI.SetSpriteScale(0.25f, 0.25f);
			krakenLifeUI.Draw(target);
			krakenLifeUI.SetPosition(background->getSize().x / 2 + ((i - 1) * krakenLifeUI.GetWidth() / 4) - kraken.GetLives() / 2 * krakenLifeUI.GetWidth() / 4, 10);
		}
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
	if (player.GetHasMultiFire())
	{
		multiFireUI.SetOpacity(player.GetHasMultiFire());
		multiFireUI.Draw(target);
	}
	else
	{
		multiFireUI.SetOpacity(player.GetHasMultiFire());
		multiFireUI.Draw(target);
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
			//add instance to vector
			cannonBalls.push_back(new CannonBall());
			cannonBalls.back()->SetPosition(spriteCaller.GetPosition().x - cannonBall.GetWidth() / 8, spriteCaller.GetPosition().y - spriteCaller.GetHeight() / 2);
			break;

		case Projectile::ANCHOR:
			//add instance to vector
			anchors.push_back(new Anchor);
			anchors.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y - spriteCaller.GetHeight() / 2);
			break;

		case Projectile::MULTIFIRE:
			//add instance to vector
			for (size_t i = 3; i > 0; --i)
			{
				cannonBalls.push_back(new CannonBall());
				cannonBalls.back()->SetVelocity(60 - (i * 20), cannonBall.GetVelocity().y);
				cannonBalls.back()->SetPosition(spriteCaller.GetPosition().x - cannonBall.GetWidth() / 8, spriteCaller.GetPosition().y - spriteCaller.GetHeight() / 2);
			}
			break;

		case Projectile::GOONCANNONBALL:
			//add instance to vector
			goonCannonBalls.push_back(new CannonBall());
			goonCannonBalls.back()->SetVelocity(0, 400);
			goonCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + cannonBall.GetHeight() / 2);
			break;

		case Projectile::SPRAYERCANNONBALL:
			//add instance to vector
			sprayerCannonBalls.push_back(new CannonBall());
			sprayerCannonBalls.back()->SetVelocity(xVelocity, sprayer.GetVelocity().y);
			sprayerCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x + spriteCaller.GetWidth() / 2, spriteCaller.GetPosition().y + cannonBall.GetHeight() / 2);
			xVelocity = -xVelocity;
			break;

		case Projectile::OLDCREWMATECANNONBALLS:
			//add instance to vector
			for (size_t i = 5; i > 0; --i)
			{
				oldCrewMateCannonBalls.push_back(new CannonBall());
				oldCrewMateCannonBalls.back()->SetVelocity(100 - (i - 1) * 20, 400);
				oldCrewMateCannonBalls.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + cannonBall.GetHeight() / 2);
			}
			break;
		case Projectile::KRAKENTENTACLES:
			//add instance to vector
			tentacleProjectiles.push_back(new Tentacle(this));
			tentacleProjectiles.back()->SetVelocity(0, 400);
			tentacleProjectiles.back()->SetPosition(spriteCaller.GetPosition().x, spriteCaller.GetPosition().y + tentacle.GetHeight() / 4);
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
			//add instance to vector
			goons.push_back(new Goon(this));
			goons.back()->SetPosition((float)RandomNumGen((int)xPosMin, (int)xPosMax), 0 - goon.GetHeight());
			cooldownClocks[0]->restart();
		break;

	case EnemyType::CHARGER:
			//add instance to vector
			chargers.push_back(new Charger(this, &player));
			chargers.back()->SetPosition(background->getSize().x / 2, 0 - charger.GetHeight());
			cooldownClocks[1]->restart();
		break;

	case EnemyType::SPRAYER:
			//add instance to vector
			sprayers.push_back(new Sprayer(this));
			sprayers.back()->SetPosition((float)RandomNumGen((int)xPosMin, (int)xPosMax), 0 - sprayer.GetHeight());
			cooldownClocks[2]->restart();
		break;

	case EnemyType::TENTACLE:
			//add instance to vector
			tentacles.push_back(new Tentacle(this));
			tentacles.back()->SetPosition(350, 400);
			cooldownClocks[5]->restart();
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
		//add instance to vector
		pirateBarricades.push_back(new PirateBarricade(this, &levelStageNumber));
		pirateBarricades.back()->SetPosition(background->getSize().x / 2 - pirateBarricade.GetWidth() / 2 - 250, 0 - pirateBarricade.GetHeight());
		cooldownClocks[3]->restart();
		break;
	case HazardType::SMALLISLAND:
		//add instance to vector
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
		//add instance to vector
		lifePickups.push_back(new LifePickup());
		lifePickups.back()->SetPosition(position);
		break;
	case PickupType::ANCHOR:
		//add instance to vector
		anchorPickups.push_back(new AnchorPickup());
		anchorPickups.back()->SetPosition(position);
		break;
	case PickupType::MULTIFIRE:
		//add instance to vector
		multiFirePickups.push_back(new MultiFirePickup());
		multiFirePickups.back()->SetPosition(position);
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
	multiFireUI.SetPosition(anchorUI.GetWidth() / 2 + 10, 30 + anchorUI.GetHeight() / 2);
	oldCrewMate.SetPosition(350, 300);
	pirateLord.SetPosition(350, 300);
	kraken.SetPosition(350, 200);

	//clean up all vectors to have no memory to begin with

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
	for (size_t i = 0; i < multiFirePickups.size(); i++)
	{
		delete multiFirePickups[i];
		multiFirePickups[i] = nullptr;
		multiFirePickups.erase(multiFirePickups.begin() + i);
	}
	for (size_t i = 0; i < tentacles.size(); i++)
	{
		delete tentacles[i];
		tentacles[i] = nullptr;
		tentacles.erase(tentacles.begin() + i);
	}

	gameRunning = true;
}

