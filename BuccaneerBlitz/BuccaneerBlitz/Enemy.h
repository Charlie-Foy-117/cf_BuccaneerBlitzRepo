#pragma once
#include "SpriteObject.h"

class LevelScreen;

class Enemy :
    public SpriteObject
{
public:

    Enemy(LevelScreen* newLevelScreen);

    void DropItem();

protected:

    int lives;
    float spawnTime;
    sf::Clock clock;

    LevelScreen* levelScreen;
};

