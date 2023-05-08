#pragma once
#include "Enemy.h"
#include "Player.h"
#include "CannonBall.h"

class LevelScreen;

class Sprayer :
    public Enemy
{
public:

    Sprayer(LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    float GetSpawnTime();
    sf::Vector2f GetVelocity();

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    sf::Clock cooldownTimer;
    float cooldown;

    LevelScreen* levelScreen;
};

