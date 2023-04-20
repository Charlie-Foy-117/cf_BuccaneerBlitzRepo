#include "PhysicsObject.h"
#include "PhysicsObject.h"
#include "VectorHelper.h"

PhysicsObject::PhysicsObject()
	: sprite()
	, collisionOffset()
	, collisionScale()
	, collisionType(CollisionType::AABB)
	, colliding(false)
{
}

void PhysicsObject::Update(sf::Time frameTime)
{
}

bool PhysicsObject::CheckColliding(PhysicsObject& other)
{
	switch (collisionType)
	{
	case CollisionType::AABB:
	{
		if (other.collisionType == CollisionType::AABB)
		{
			return GetAABB().intersects(other.GetAABB());
		}
		else
		{
			//handles a rectangle colliding with a circle
			sf::Vector2f nearestPointToCircle = other.GetCollisionCentre(); //actual circle centre
			sf::FloatRect thisAABB = GetAABB();
			//clamp the circle centre to min and max aabb
			nearestPointToCircle.x = fmaxf(thisAABB.left, fminf(nearestPointToCircle.x, thisAABB.left + thisAABB.width));
			nearestPointToCircle.y = fmaxf(thisAABB.top, fminf(nearestPointToCircle.y, thisAABB.top + thisAABB.height));
			sf::Vector2f displacement = nearestPointToCircle - other.GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = other.GetCircleColliderRadius();

			return squareDistance <= circleRadius * circleRadius;
		}
	}
	break;
	case CollisionType::CIRCLE:
	{
		if (other.collisionType == CollisionType::CIRCLE)
		{
			//get the vector representing the displacement between the two circles
			sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

			//get the magnitude of that vector, which is how far apart the circle centres
			float sqaureDistance = VectorHelper::SquareMagnitude(displacement); //todo

			//compare that to the comvined radii of the two circles
			float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

			return sqaureDistance <= combinedRadii * combinedRadii;
		}
	}
	break;
	default:
		break;
	};
}

void PhysicsObject::HandleCollision(PhysicsObject& other)
{
}

sf::Vector2f PhysicsObject::GetCollisionDepth(PhysicsObject other)
{
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();

	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();

	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width / 2.0f + otherAABB.width / 2.0f;
	minDistance.y = thisAABB.height / 2.0f + otherAABB.height / 2.0f;

	sf::Vector2f actualDistance = otherCentre - thisCentre;

	if (actualDistance.x < 0)
	{
		minDistance.x = -minDistance.x;
	}
	if (actualDistance.y < 0)
	{
		minDistance.y = -minDistance.y;
	}

	return actualDistance - minDistance;
}

void PhysicsObject::SetEnumUsed(CollisionType newEnum)
{
	collisionType = newEnum;
}

sf::Vector2f PhysicsObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width / 2.0f;
	centre.y += bounds.height / 2.0f;

	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;

	return centre;
}

float PhysicsObject::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	if (bounds.width > bounds.height)
		return bounds.width / 2.0f;
	else
		return bounds.height / 2.0f;
}

sf::FloatRect PhysicsObject::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	sf::Vector2f centre = GetCollisionCentre();

	bounds.left = centre.x - bounds.width / 2.0f;
	bounds.top = centre.y - bounds.height / 2.0f;

	return bounds;
}

