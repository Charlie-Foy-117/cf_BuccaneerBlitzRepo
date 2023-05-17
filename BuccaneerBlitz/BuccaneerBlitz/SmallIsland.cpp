#include "SmallIsland.h"
#include "AssetManager.h"
#include "LevelScreen.h"

SmallIsland::SmallIsland(LevelScreen* newLevelScreen)
	: Hazards()
	, acceleration()
	, velocity(0, 150)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_SmallIsland_PNG.png"));

	spawnTime = 10.0f;
}

void SmallIsland::Update(sf::Time frameTime)
{
	//moves island down screen
	sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;
	SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());
	velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
}

void SmallIsland::HandleCollision(SpriteObject& other)
{
	if (typeid(other).name() == typeid(Player).name())
	{
		ModifyLives(-1);
		other.ModifyLives(-1);
	}
	else
	{
		levelScreen->SpawnHazard(HazardType::SMALLISLAND);
	}
}

float SmallIsland::GetSpawnTime()
{
	return spawnTime;
}
