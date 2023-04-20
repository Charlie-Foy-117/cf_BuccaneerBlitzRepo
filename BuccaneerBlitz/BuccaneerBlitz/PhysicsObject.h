#pragma once
#include <SFML/Graphics.hpp>

enum class CollisionType
{
	AABB,
	CIRCLE
};

class PhysicsObject
{
public:

	PhysicsObject();

	void Update(sf::Time frameTime);

	bool CheckColliding(PhysicsObject& other);
	virtual void HandleCollision(PhysicsObject& other);
	sf::Vector2f GetCollisionDepth(PhysicsObject other);

	void SetEnumUsed(CollisionType newEnum);

protected:

	sf::Sprite sprite;

	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;
	CollisionType collisionType;

private:

	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();
	sf::FloatRect GetAABB();

	sf::Vector2f position;
	bool colliding;
};

