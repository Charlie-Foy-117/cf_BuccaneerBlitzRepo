#pragma once
#include "PhysicsObject.h"
class SideBarrier :
    public PhysicsObject
{
public:

    SideBarrier(sf::RenderWindow* newWindow, int* newLevelNumber);

    void ResetPosition(std::string side);

    void HandleCollision(PhysicsObject& other) override;

    void UpdateSpriteAsset(int newLevelNumber);
private:
    

    sf::RenderWindow* window;
    int* levelNumber;
};

