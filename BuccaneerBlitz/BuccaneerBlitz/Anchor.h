#pragma once
#include "PhysicsObject.h"
class Anchor :
    public PhysicsObject
{
public:

    Anchor();

    void Update(sf::Time frameTime) override;
    void SetVelocity(float newX, float newY);

    void HandleCollision(PhysicsObject& other) override;
};

