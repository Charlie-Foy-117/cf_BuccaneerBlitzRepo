#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "SideBarrier.h"
#include "Player.h"
#include "CannonBall.h"
#include "Timer.h"
#include "Goon.h"


enum Projectile
{
    CANNONBALL,
    ANCHOR,
    MULTIFIRE
};

enum EnemyType
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

    void TriggerEndState(bool win);

    void AddToVector(Projectile projectileType);
    void SpawnEnemy(EnemyType enemyType);

    int RandomNumGen(int min, int max);

    Player player;

private:

    void Restart();

    int levelNumber;

    bool gameRunning;
    sf::RenderWindow* background;
    SideBarrier sideBarrierLeft;
    SideBarrier sideBarrierRight;
    std::vector<CannonBall*> cannonBalls;
    Timer timer;

    sf::Clock cooldownClock;
    std::vector<Goon*> goons;
};


