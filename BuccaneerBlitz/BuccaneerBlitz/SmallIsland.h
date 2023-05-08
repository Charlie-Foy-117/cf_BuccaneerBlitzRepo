#pragma once
#include "Hazards.h"

class LevelScreen;

class SmallIsland :
    public Hazards
{
public:

    SmallIsland(LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    float GetSpawnTime();

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    LevelScreen* levelScreen;
};

