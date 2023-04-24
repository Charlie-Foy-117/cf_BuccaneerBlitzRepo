#pragma once
#include "Enemy.h"

class LevelScreen;

class Goon :
    public Enemy
{
public:

    Goon(LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    float GetSpawnTime();
    void SpawnGoon();

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    LevelScreen* levelScreen;

    sf::Clock cooldownTimer;
};
