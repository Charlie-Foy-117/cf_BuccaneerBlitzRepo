#pragma once
#include "SpriteObject.h"
class Pickups :
    public SpriteObject
{
public:

    Pickups();
    void Update(sf::Time frameTime) override;

private:

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

