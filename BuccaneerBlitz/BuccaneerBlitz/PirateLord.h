#pragma once
#include "Enemy.h"

class LevelScreen;
class Player;

class PirateLord :
    public Enemy
{
public:

    PirateLord(LevelScreen* newLevelScreen, Player* newPlayer);
    void HandleCollision(SpriteObject& other) override;
    void Update(sf::Time frameTime) override;

private:

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float speed;

    sf::Clock cooldownTimer;
    float cooldown;

    LevelScreen* levelScreen;
    Player* player;
};

