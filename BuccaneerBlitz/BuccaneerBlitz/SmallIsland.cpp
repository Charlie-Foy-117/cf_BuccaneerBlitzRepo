#include "SmallIsland.h"
#include "AssetManager.h"
#include "LevelScreen.h"

SmallIsland::SmallIsland(LevelScreen* newLevelScreen)
	: Hazards()
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_SmallIsland_PNG.png"));

	spawnTime = 10.0f;
	velocity = sf::Vector2f(0, 150);
}

void SmallIsland::Update(sf::Time frameTime)
{
	//moves island down screen
	PhysicsObject::Update(frameTime);
}

void SmallIsland::HandleCollision(PhysicsObject& other)
{
	if (typeid(other).name() == typeid(Player).name())
	{
		ModifyLives(-1);
		other.ModifyLives(-1);
	}
	else
	{
		//if statements are false the spawn a new instance
		//this is to handle when objects spawns outside playing area
		levelScreen->SpawnHazard(HazardType::SMALLISLAND);
	}
}

float SmallIsland::GetSpawnTime()
{
	return spawnTime;
}
