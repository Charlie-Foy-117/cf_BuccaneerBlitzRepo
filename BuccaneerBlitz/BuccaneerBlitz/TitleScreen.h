#pragma once
#include "Screen.h"
#include "Text.h"

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

    Text text;
};

