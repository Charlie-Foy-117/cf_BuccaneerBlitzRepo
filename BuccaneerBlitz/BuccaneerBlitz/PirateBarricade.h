#pragma once
#include "Hazards.h"

class LevelScreen;

class PirateBarricade :
    public Hazards
{
public:

    PirateBarricade(LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    float GetSpawnTime();

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    LevelScreen* levelScreen;

};

