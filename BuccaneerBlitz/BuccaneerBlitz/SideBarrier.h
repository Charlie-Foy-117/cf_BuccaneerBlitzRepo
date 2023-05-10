#pragma once
#include "SpriteObject.h"
class SideBarrier :
    public SpriteObject
{
public:

    SideBarrier(sf::RenderWindow* newWindow, int* newLevelNumber);

    void ResetPosition(std::string side);

    void HandleCollision(SpriteObject& other) override;

private:
    void UpdateSpriteAsset(int newLevelNumber);

    sf::RenderWindow* window;
    int* levelNumber;
};

