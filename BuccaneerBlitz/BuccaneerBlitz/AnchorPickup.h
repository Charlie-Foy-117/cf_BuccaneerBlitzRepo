#pragma once
#include "Pickups.h"
class AnchorPickup :
    public Pickups
{
public:

    AnchorPickup();

    void HandleCollision(PhysicsObject& other) override;
};

