#pragma once
#include "Enemy.h"

class LevelScreen;
class Player;

class PirateLord :
    public Enemy
{
public:

    PirateLord(sf::RenderWindow* newWindow, LevelScreen* newLevelScreen, Player* newPlayer);
    void HandleCollision(SpriteObject& other) override;
    void Update(sf::Time frameTime) override;

private:

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
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

