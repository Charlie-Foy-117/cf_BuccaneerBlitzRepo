#pragma once
#include "Enemy.h"

class LevelScreen;

class OldCrewMate :
    public Enemy
{
public:

    OldCrewMate(LevelScreen* newLevelScreen);
    void HandleCollision(PhysicsObject& other) override;
    void Update(sf::Time frameTime) override;

private:

    sf::Clock cooldownTimer;
    float cooldown;

    LevelScreen* levelScreen;
};

