#pragma once
#include "SpriteObject.h"

enum class CollisionType
{
	AABB,
	CIRCLE,
	BOSSROOM
};

class PhysicsObject :
    public SpriteObject
{
public:

	PhysicsObject();

	void Update(sf::Time frameTime) override;
	void Draw(sf::RenderTarget& target) override;

	bool CheckColliding(PhysicsObject other);
	void SetColliding(bool newColliding);

	virtual void HandleCollision(PhysicsObject& other);

	sf::Vector2f GetCollisionDepth(PhysicsObject other);

	void SetEnumUsed(CollisionType newEnum);

	void SetCollisionOffest(float xOffset, float yOffset);

protected:

	virtual void UpdateAcceleration();

	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;
	CollisionType collisionType;

	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f twoFramesOldPosition;

	bool hasDrag;

private:


	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();
	sf::FloatRect GetAABB();

	bool colliding;
};

