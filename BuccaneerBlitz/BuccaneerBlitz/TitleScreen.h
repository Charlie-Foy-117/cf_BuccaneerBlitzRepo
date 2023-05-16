#pragma once
#include "Screen.h"
#include "Text.h"
#include "Score.h"

class Game;

class TitleScreen :
    public Screen
{
public:

    TitleScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

private:

    Game* game;
    sf::RenderWindow* window;

    Text text;
    Text scoreText;

    Score score;

    sf::Clock cooldownTimer;
    float cooldown;
};

