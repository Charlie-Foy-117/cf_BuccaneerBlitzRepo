#pragma once
#include "PhysicsObject.h"

class LevelScreen;

class Enemy :
    public PhysicsObject
{
public:

    Enemy(LevelScreen* newLevelScreen);

    void DropItem();
    void KillBoss();

    float GetBonusTime();
    float GetSpawnTime();

protected:

    float spawnTime;
    sf::Clock clock;

    LevelScreen* levelScreen;

    float bonusTime;

    sf::Sound attackSound;
};


