#include "OldCrewMate.h"
#include "AssetManager.h"

OldCrewMate::OldCrewMate(LevelScreen* newLevelScreen)
	: Enemy(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/cf_OldCrewMate_PNG.png"));
	sprite.setScale(0.5f, 0.5f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setRotation(180);
	collisionScale = sf::Vector2f(0.5f, 1.0f);
}
