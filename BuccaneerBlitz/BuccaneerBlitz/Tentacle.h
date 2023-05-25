#pragma once
#include "Enemy.h"
#include "SideBarrier.h"

class Tentacle :
    public Enemy
{
public:

    Tentacle(LevelScreen* newLevelScreen);
    void HandleCollision(PhysicsObject& other) override;
    void Update(sf::Time frameTime) override;

    void SetVelocity(float newX, float newY);

private:

    LevelScreen* levelScreen;

    bool flipX;
};

