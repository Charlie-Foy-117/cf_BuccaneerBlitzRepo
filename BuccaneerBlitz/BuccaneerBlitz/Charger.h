#pragma once
#include "Enemy.h"

class LevelScreen;
class Player;

class Charger :
    public Enemy
{
public:

    Charger(LevelScreen* newLevelScreen, Player* newPlayer);

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    float GetSpawnTime();

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    float speed;
    float trackingDistance;

    LevelScreen* levelScreen;
    Player* player;

    sf::Clock cooldownTimer;
    float cooldown;
};

