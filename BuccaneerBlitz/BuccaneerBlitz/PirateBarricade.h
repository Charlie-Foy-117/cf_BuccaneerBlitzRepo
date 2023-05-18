#pragma once
#include "Hazards.h"
#include "Anchor.h"
#include "Player.h"

class LevelScreen;

class PirateBarricade :
    public Hazards
{
public:

    PirateBarricade(LevelScreen* newLevelScreen, int* newLevelNumber);

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    float GetSpawnTime();

private:

    void UpdateSpriteAsset(int newLevelNumber);

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    LevelScreen* levelScreen;
    int* levelNumber;

};

