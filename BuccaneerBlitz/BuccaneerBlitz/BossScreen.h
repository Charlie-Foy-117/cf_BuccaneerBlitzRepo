#pragma once
#include "Screen.h"
#include "BossRoom1Barrier.h"

class Game;

class BossScreen :
    public Screen
{
public:

    BossScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void TriggerEndState();

private:

    BossRoom1Barrier bossRoom1Barrier;
};

