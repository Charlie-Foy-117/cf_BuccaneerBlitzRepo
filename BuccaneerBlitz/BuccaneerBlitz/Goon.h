#pragma once
#include "Enemy.h"

class Goon :
    public Enemy
{
public:

    Goon(LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void HandleCollision(PhysicsObject& other) override;


private:

    sf::Clock cooldownTimer;
    float cooldown;
};

