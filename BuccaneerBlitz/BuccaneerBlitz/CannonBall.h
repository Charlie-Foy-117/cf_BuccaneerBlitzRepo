#pragma once
#include "PhysicsObject.h"
#include "SideBarrier.h"
#include "BossRoomBarrier.h"
#include "Tentacle.h"


class CannonBall :
    public PhysicsObject
{
public:

    CannonBall();

    void Update(sf::Time frameTime) override;
    void SetVelocity(float newX, float newY);
    sf::Vector2f GetVelocity();

    void HandleCollision(PhysicsObject& other) override;

private:

    sf::Sound collisionSound;
};

