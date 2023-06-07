#pragma once
#include "Screen.h"
#include "Text.h"
#include "Score.h"
#include "TitleCard.h"
#include "Overlay.h"
#include "Backplate.h"
#include "Buoy.h"

class Game;

class TitleScreen :
    public Screen
{
public:

    TitleScreen(Game* newGamePointer);

    ~TitleScreen() override;

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

private:

    Game* game;
    sf::RenderWindow* window;

    Text text;
    Text scoreText;
    Text toolTip;
    TitleCard titleCard;
    Overlay overlay;
    Backplate backplate;
    Buoy buoy;

    Score score;

    sf::Clock cooldownTimer;
    float cooldown;
};

