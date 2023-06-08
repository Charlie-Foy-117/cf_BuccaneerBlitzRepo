#pragma once
#include "Enemy.h"

class Player;

class Charger :
    public Enemy
{
public:

    Charger(LevelScreen* newLevelScreen, Player* newPlayer);

    void Update(sf::Time frameTime) override;
    void HandleCollision(PhysicsObject& other) override;

private:

    float speed;

    Player* player;

    sf::Clock cooldownTimer;
    float cooldown;
};

