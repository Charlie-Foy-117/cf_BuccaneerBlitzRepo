#pragma once
#include "Enemy.h"
#include "SideBarrier.h"

class Tentacle :
    public Enemy
{
public:

    Tentacle(LevelScreen* newLevelScreen);
    void HandleCollision(SpriteObject& other) override;
    void Update(sf::Time frameTime) override;

private:

    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    LevelScreen* levelScreen;

    bool flipX;
};

