#pragma once
#include "Screen.h"
#include "BossRoom1Barrier.h"
#include "Player.h"
#include "Timer.h"
#include "Score.h"
#include "LifeUI.h"
#include "AnchorUI.h"

class Game;
class LevelScreen;

class BossScreen :
    public Screen
{
public:

    BossScreen(Game* newGamePointer, LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void TriggerEndState();

private:

    BossRoom1Barrier bossRoom1Barrier;
    Player player;

    Timer timer;
    Score score;

    LifeUI lifeUI;
    AnchorUI anchorUI;

    LevelScreen* levelScreen;
    Game* game;
};

