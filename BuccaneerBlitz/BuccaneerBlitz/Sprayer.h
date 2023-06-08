#pragma once
#include "Enemy.h"
#include "Player.h"
#include "CannonBall.h"

class Sprayer :
    public Enemy
{
public:

    Sprayer(LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void HandleCollision(PhysicsObject& other) override;

    sf::Vector2f GetVelocity();

private:

    sf::Clock cooldownTimer;
    float cooldown;
};

