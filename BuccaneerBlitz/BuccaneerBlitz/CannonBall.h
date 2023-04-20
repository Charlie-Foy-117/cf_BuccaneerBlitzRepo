#pragma once
#include "SpriteObject.h"


class CannonBall :
    public SpriteObject
{
public:

    CannonBall();

    void Update(sf::Time frameTime) override;

    void HandleCollision(SpriteObject& other) override;

    float GetWidth();
    float GetHeight();

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    float width;
    float height;


};

