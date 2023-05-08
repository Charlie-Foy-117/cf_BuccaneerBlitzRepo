#pragma once
#include "SpriteObject.h"
class Anchor :
    public SpriteObject
{
public:

    Anchor();

    void Update(sf::Time frameTime) override;
    void SetVelocity(float newX, float newY);

    void HandleCollision(SpriteObject& other) override;

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

};

