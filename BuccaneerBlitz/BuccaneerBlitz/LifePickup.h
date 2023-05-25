#pragma once
#include "Pickups.h"

class LifePickup :
    public Pickups
{
public:

    LifePickup();

    void HandleCollision(PhysicsObject& other);

};

