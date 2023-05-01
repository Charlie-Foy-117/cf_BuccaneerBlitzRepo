#include "Charger.h"
#include "AssetManager.h"
#include "Player.h"

Charger::Charger(LevelScreen* newLevelScreen, Player* newPlayer)
	: Enemy()
	, acceleration()
	, velocity(0, 0)
    , speed(400.0f)
    , trackingDistance(1000)
	, levelScreen(newLevelScreen)
	, player(newPlayer)
	, cooldownTimer()
	, cooldown(1.0f)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_Charger_PNG.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setRotation(180);
    sprite.scale(0.5f, 0.5f);

    collisionScale = sf::Vector2f(0.45f, 0.95f);

    spawnTime = 7.0f;
}

void Charger::Update(sf::Time frameTime)
{
    sf::Vector2f chargerPos = sprite.getPosition();
    
    //calculate the distance between the enemy and the player
    float distance = std::sqrt(std::pow(player->GetPosition().x - chargerPos.x, 2) + std::pow(player->GetPosition().y - chargerPos.y, 2));

    //calculate the direction from the enemy to the player
    sf::Vector2f direction = player->GetPosition() - chargerPos;

    //normalize the direction vector
    if (distance != 0)
    {
        sf::Vector2f unitDirection = direction / distance;

        // Set the enemy's velocity to the normalized direction vector multiplied by the speed
        velocity = unitDirection * speed;

        //update the enemy's position using its velocity
        chargerPos += velocity * frameTime.asSeconds();
    }
    //update sprites position
    sprite.setPosition(chargerPos);
}

void Charger::HandleCollision(SpriteObject& other)
{
}

float Charger::GetSpawnTime()
{
	return spawnTime;
}
