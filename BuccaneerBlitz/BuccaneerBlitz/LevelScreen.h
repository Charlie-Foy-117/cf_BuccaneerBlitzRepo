#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

#include "SideBarrier.h"

#include "Player.h"
#include "CannonBall.h"
#include "Anchor.h"
#include "LifePickup.h"
#include "AnchorPickup.h"

#include "Timer.h"
#include "Score.h"

#include "Goon.h"
#include "Charger.h"
#include "PirateBarricade.h"

#include "EndPanel.h"
#include "LifeUI.h"
#include "AnchorUI.h"

enum class Projectile
{
    CANNONBALL,
    ANCHOR,
    MULTIFIRE,
    ENEMYCANNONBALL
};

enum class EnemyType
{
    GOON,
    SPRAYER,
    CHARGER
};

enum class HazardType
{
    PIRATEBARRICADE,
    SMALLISLAND
};

enum class PickupType
{
    LIFE,
    ANCHOR,
    MULTIFIRE
};

class Game;

class LevelScreen :
    public Screen
{
public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
    void BackgroundColour(int currentLevel);

    void TriggerEndState();

    void SpawnProjectile(Projectile projectileType, SpriteObject& spriteCaller);
    void SpawnEnemy(EnemyType enemyType);
    void SpawnHazard(HazardType hazardType);
    void SpawnPickUp(PickupType pickupType, SpriteObject& spriteCaller);
    int RandomNumGen(int min, int max);

    Player player;

    int levelStageNumber;
    bool gameRunning;

private:

    //TODO: fill function to load boss level/next level
    void LoadLevel(int currentStage);
    void Restart();

    sf::RenderWindow* background;
    Game* game;
    SideBarrier sideBarrierLeft;
    SideBarrier sideBarrierRight;
    Charger charger;
    Goon goon;

    std::vector<CannonBall*> cannonBalls;
    std::vector<Anchor*> anchors;
    std::vector<CannonBall*> enemyCannonBalls;
    std::vector<PirateBarricade*> pirateBarricades;

    Timer timer;
    Score score;

    LifeUI lifeUI;
    AnchorUI anchorUI;
    EndPanel endPanel;

    std::vector<sf::Clock*> cooldownClocks;
    std::vector<Goon*> goons;
    std::vector<Charger*> chargers;

    std::vector<LifePickup*> lifePickups;
    std::vector<AnchorPickup*> anchorPickups;
};


