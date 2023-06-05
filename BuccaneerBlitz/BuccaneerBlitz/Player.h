#pragma once
#include "PhysicsObject.h"
#include "CannonBall.h"

class LevelScreen;

class Player :
    public PhysicsObject
{
public:

    Player(sf::RenderWindow* newWindow, LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;

    void HandleCollision(PhysicsObject& other) override;

    void FireCannonBall(float newCooldown);
    void FireAnchor(float newCooldown);
    void FireMultiFire(float newCooldown);

    bool GetHasAnchor();
    bool GetHasMultiFire();

private:
    void UpdateAcceleration() override;

    sf::RenderWindow* window;
    LevelScreen* levelScreen;

    sf::Clock cooldownTimer;
    float cooldown;

    bool hasAnchor;
    bool hasMultiFire;

    sf::Sound attackSound;
    sf::Sound pickupSound;
    sf::Sound collisionSound;
};

