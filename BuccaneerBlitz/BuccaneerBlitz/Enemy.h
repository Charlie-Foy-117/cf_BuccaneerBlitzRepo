#pragma once
#include "SpriteObject.h"
class Enemy :
    public SpriteObject
{
public:

    Enemy();

protected:

    int lives;
    float spawnTime;
};

