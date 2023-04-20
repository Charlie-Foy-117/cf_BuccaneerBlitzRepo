#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "SideBarrier.h"
#include "Player.h"
#include "CannonBall.h"


enum Projectile
{
    CANNONBALL,
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

    void TriggerEndState(bool win);

    void AddToVector(Projectile projectileType);

private:

    void Restart();

    bool gameRunning;
    sf::RenderWindow* background;
    Player player;
    SideBarrier sideBarrierLeft;
    SideBarrier sideBarrierRight;
    std::vector<CannonBall*> cannonBalls;
};


