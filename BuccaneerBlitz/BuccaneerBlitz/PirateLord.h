#pragma once
#include "Enemy.h"

class LevelScreen;
class Player;

class PirateLord :
    public Enemy
{
public:

    PirateLord(sf::RenderWindow* newWindow, LevelScreen* newLevelScreen, Player* newPlayer);
    void HandleCollision(PhysicsObject& other) override;
    void Update(sf::Time frameTime) override;

private:

    float speed;
    float tolerance;
    float originalY;
    bool xPositionMatched;

    sf::Clock cooldownTimer;
    float cooldown;

    LevelScreen* levelScreen;
    sf::RenderWindow* window;
    Player* player;
};

