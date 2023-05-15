#pragma once
#include "SpriteObject.h"
#include "SideBarrier.h"
#include "BossRoomBarrier.h"


class CannonBall :
    public SpriteObject
{
public:

    CannonBall();

    void Update(sf::Time frameTime) override;
    void SetVelocity(float newX, float newY);
    sf::Vector2f GetVelocity();

    void HandleCollision(SpriteObject& other) override;

private:

    sf::Vector2f acceleration;
    sf::Vector2f velocity;
};

