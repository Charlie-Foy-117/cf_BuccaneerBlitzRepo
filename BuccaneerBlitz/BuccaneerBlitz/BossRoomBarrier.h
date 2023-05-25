#pragma once
#include "PhysicsObject.h"

class BossRoomBarrier :
    public PhysicsObject
{
public:

    BossRoomBarrier(sf::RenderWindow* newWindow, int* newLevelNumber);

    void HandleCollision(PhysicsObject& other) override;
    void UpdateSpriteAsset(int newLevelNumber);

private:

    sf::RenderWindow* window;
    int* levelNumber;
    
};

