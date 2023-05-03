#pragma once
#include <SFML/Graphics.hpp>
enum class CollisionType
{
	AABB,
	CIRCLE
};

class SpriteObject
{
public:

	SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	bool CheckColliding(SpriteObject other);
	void SetColliding(bool newColliding);

	virtual void HandleCollision(SpriteObject& other);

	sf::Vector2f GetCollisionDepth(SpriteObject other);

	void SetEnumUsed(CollisionType newEnum);

	float GetHeight();
	float GetWidth();

	void SetAlive(bool newAlive);
	bool GetAlive();
	int GetLives();
	void LoseLife();
	void GainLife();

protected:

	sf::Sprite sprite;

	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;
	CollisionType collisionType;

	bool alive;

	int lives;

private:


	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();
	sf::FloatRect GetAABB();


	sf::Vector2f position;
	bool colliding;
};

