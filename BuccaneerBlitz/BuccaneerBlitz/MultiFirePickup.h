#pragma once
#include "Pickups.h"
class MultiFirePickup :
    public Pickups
{
public:

    MultiFirePickup();

    void HandleCollision(PhysicsObject& other);

};

