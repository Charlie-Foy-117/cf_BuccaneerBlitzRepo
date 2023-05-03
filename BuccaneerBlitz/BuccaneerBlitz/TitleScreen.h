#pragma once
#include "Screen.h"
class TitleScreen :
    public Screen
{
public:

    TitleScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
};

