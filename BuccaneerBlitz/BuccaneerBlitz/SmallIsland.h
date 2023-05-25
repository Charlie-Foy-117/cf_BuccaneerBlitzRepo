#pragma once
#include "Hazards.h"
#include "Player.h"

class LevelScreen;

class SmallIsland :
    public Hazards
{
public:

    SmallIsland(LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void HandleCollision(PhysicsObject& other) override;

    float GetSpawnTime();

private:

    LevelScreen* levelScreen;
};

