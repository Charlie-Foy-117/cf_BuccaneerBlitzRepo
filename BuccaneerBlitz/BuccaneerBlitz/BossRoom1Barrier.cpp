#include "BossRoom1Barrier.h"
#include "AssetManager.h"

BossRoom1Barrier::BossRoom1Barrier(sf::RenderWindow* newWindow)
	: SpriteObject()
	, window(newWindow)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Environment/cf_BossRoom1Barrier_PNG.png"));
	sprite.setScale(2.4f, 2.4f);

	SetEnumUsed(CollisionType::BOSSROOM1);
}

void BossRoom1Barrier::HandleCollision(SpriteObject& other)
{
	SpriteObject::HandleCollision(other);
}
