#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "SideBarrier.h"
#include "Player.h"
#include "CannonBall.h"
#include "Timer.h"
#include "Score.h"
#include "Goon.h"


enum class Projectile
{
    CANNONBALL,
    ANCHOR,
    MULTIFIRE
};

enum class EnemyType
{
    GOON,
    SPRAYER,
    CHARGER
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

    void TriggerEndState(bool win);

    void SpawnProjectile(Projectile projectileType);
    void SpawnEnemy(EnemyType enemyType);

    int RandomNumGen(int min, int max);

    Player player;

    int levelNumber;
private:

    void Restart();

    bool gameRunning;
    sf::RenderWindow* background;
    SideBarrier sideBarrierLeft;
    SideBarrier sideBarrierRight;
    std::vector<CannonBall*> cannonBalls;
    Timer timer;
    Score score;

    sf::Clock cooldownClock;
    std::vector<Goon*> goons;
};


