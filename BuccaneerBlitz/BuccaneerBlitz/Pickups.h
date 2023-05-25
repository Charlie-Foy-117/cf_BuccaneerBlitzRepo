#pragma once
#include "PhysicsObject.h"
class Pickups :
    public PhysicsObject
{
public:

    Pickups();
    void Update(sf::Time frameTime) override;
};

