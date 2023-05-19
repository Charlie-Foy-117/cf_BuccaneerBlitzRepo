#pragma once
#include "Pickups.h"
class MultiFirePickup :
    public Pickups
{
public:

    MultiFirePickup();

    void HandleCollision(SpriteObject& other);

};

