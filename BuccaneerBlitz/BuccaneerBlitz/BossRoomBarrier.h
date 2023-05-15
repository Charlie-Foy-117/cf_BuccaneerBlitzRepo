#pragma once
#include "SpriteObject.h"

class BossRoomBarrier :
    public SpriteObject
{
public:

    BossRoomBarrier(sf::RenderWindow* newWindow, int* newLevelNumber);

    void HandleCollision(SpriteObject& other) override;
    void UpdateSpriteAsset(int newLevelNumber);

private:

    sf::RenderWindow* window;
    int* levelNumber;
    
};

