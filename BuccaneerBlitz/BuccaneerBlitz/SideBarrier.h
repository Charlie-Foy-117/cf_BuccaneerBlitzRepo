#pragma once
#include "SpriteObject.h"
class SideBarrier :
    public SpriteObject
{
public:

    SideBarrier(sf::RenderWindow* newWinow);

    void ResetPosition(std::string side);

    void HandleCollision(SpriteObject& other) override;

private:

    sf::RenderWindow* window;
};

