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
    void HandleCollision(PhysicsObject& other) override;

private:

    float speed;

    Player* player;
    LevelScreen* levelScreen;

    sf::Clock cooldownTimer;
    float cooldown;
};

