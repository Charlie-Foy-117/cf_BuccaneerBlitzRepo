#pragma once
#include "SpriteObject.h"

class BossRoom1Barrier :
    public SpriteObject
{
public:

    BossRoom1Barrier(sf::RenderWindow* newWindow);

    void HandleCollision(SpriteObject& other) override;

private:

    sf::RenderWindow* window;
};

