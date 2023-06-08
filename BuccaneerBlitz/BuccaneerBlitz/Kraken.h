#pragma once
#include "Enemy.h"
#include "SideBarrier.h"

class Kraken :
    public Enemy
{
public:

    Kraken(LevelScreen* newLevelScreen);
    void HandleCollision(PhysicsObject& other) override;
    void Update(sf::Time frameTime) override;

private:

    sf::Clock cooldownTimer;
    float cooldown;
};

