#pragma once
#include "SpriteObject.h"
#include "CannonBall.h"

class LevelScreen;

class Player :
    public SpriteObject
{
public:

    Player(sf::RenderWindow* newWindow, LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;

    void HandleCollision(SpriteObject& other) override;

    void FireCannonBall(float newCooldown);

    float GetHeight();
    float GetWidth();

private:
    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPosition;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    CannonBall cannonBall;

    sf::RenderWindow* window;
    LevelScreen* levelScreen;

    sf::Clock cooldownTimer;
    float cooldown;

    float width;
    float height;
};

