#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

#include "SideBarrier.h"
#include "BossRoomBarrier.h"

#include "Player.h"
#include "CannonBall.h"
#include "Anchor.h"
#include "LifePickup.h"
#include "AnchorPickup.h"
#include "MultiFirePickup.h"

#include "Timer.h"
#include "Score.h"

#include "OldCrewMate.h"
#include "PirateLord.h"
#include "Kraken.h"
#include "Tentacle.h"
#include "Goon.h"
#include "Charger.h"
#include "Sprayer.h"
#include "PirateBarricade.h"
#include "SmallIsland.h"

#include "EndPanel.h"
#include "LifeUI.h"
#include "AnchorUI.h"
#include "MultiFireUI.h"

enum class Projectile
{
    CANNONBALL,
    ANCHOR,
    MULTIFIRE,
    GOONCANNONBALL,
    SPRAYERCANNONBALL,
    OLDCREWMATECANNONBALLS
};

enum class EnemyType
{
    GOON,
    SPRAYER,
    CHARGER,
    TENTACLE
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
    void SpawnPickUp(PickupType pickupType, sf::Vector2f position);
    int RandomNumGen(int min, int max);

    Player player;

    int levelStageNumber;
    bool gameRunning;

private:

    void Restart();

    sf::RenderWindow* background;
    Game* game;
    SideBarrier sideBarrierLeft;
    SideBarrier sideBarrierRight;
    BossRoomBarrier bossRoomBarrier;
    CannonBall cannonBall;
    Anchor anchor;
    Charger charger;
    Goon goon;
    Sprayer sprayer;
    Tentacle tentacle;
    PirateBarricade pirateBarricade;
    SmallIsland smallIsland;

    std::vector<CannonBall*> cannonBalls;
    std::vector<Anchor*> anchors;
    std::vector<CannonBall*> goonCannonBalls;
    std::vector<CannonBall*> sprayerCannonBalls;
    std::vector<CannonBall*> oldCrewMateCannonBalls;
    std::vector<PirateBarricade*> pirateBarricades;
    std::vector<SmallIsland*> smallIslands;

    OldCrewMate oldCrewMate;
    PirateLord pirateLord;
    Kraken kraken;
    std::vector<Tentacle*> tentacles;

    Timer timer;
    Score score;

    LifeUI lifeUI;
    AnchorUI anchorUI;
    MultiFireUI multiFireUI;
    LifeUI oldCrewMateLifeUI;
    LifeUI pirateLordLifeUI;
    LifeUI krakenLifeUI;
    EndPanel endPanel;

    std::vector<sf::Clock*> cooldownClocks;
    std::vector<Goon*> goons;
    std::vector<Charger*> chargers;
    std::vector<Sprayer*> sprayers;

    std::vector<LifePickup*> lifePickups;
    std::vector<AnchorPickup*> anchorPickups;
    std::vector<MultiFirePickup*> multiFirePickups;

    //controls direction for sprayer cannonballs
    float xVelocity;

    //controls colour of background
    sf::Color targetColor;
    sf::Color currentColor;
};


