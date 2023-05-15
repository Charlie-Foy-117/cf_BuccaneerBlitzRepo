#pragma once
#include "Enemy.h"

class LevelScreen;

class OldCrewMate :
    public Enemy
{
public:

    OldCrewMate(LevelScreen* newLevelScreen);
    void HandleCollision(SpriteObject& other) override;
    void Update(sf::Time frameTime) override;

private:

    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    sf::Clock cooldownTimer;
    float cooldown;

    LevelScreen* levelScreen;
};

