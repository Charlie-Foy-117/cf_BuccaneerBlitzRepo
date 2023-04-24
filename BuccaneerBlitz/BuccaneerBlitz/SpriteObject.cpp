#include "SpriteObject.h"
#include "VectorHelper.h"


SpriteObject::SpriteObject()
	: sprite()
	, position(0, 0)
	, collisionOffset(0, 0)
	, collisionScale(1, 1)
	, collisionType(CollisionType::AABB)
	, colliding(false)
	, alive(true)
{
}

void SpriteObject::Update(sf::Time frameTime)
{

}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	if (!alive)
	{
		return;
	}

	target.draw(sprite);

	bool drawCollider = false;
	if (drawCollider)
	{
		switch (collisionType)
		{
		case CollisionType::AABB:
		{
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));
			sf::Color collisionColour = sf::Color::Green;
			//turn this red if a collision is occurring
			if (colliding)
			{
				collisionColour = sf::Color::Red;
			}
			collisionColour.a = 100;
			rectangle.setFillColor(collisionColour);

			target.draw(rectangle);
		}
		break;
		case CollisionType::CIRCLE:
		{
			sf::CircleShape circle;

			sf::Vector2f shapePosition = GetCollisionCentre();
			float circleRadius = GetCircleColliderRadius();
			shapePosition.x -= circleRadius;
			shapePosition.y -= circleRadius;

			circle.setPosition(shapePosition);
			circle.setRadius(circleRadius);
			sf::Color collisionColour = sf::Color::Green;
			//turn this red if a collision is occurring
			if (colliding)
			{
				collisionColour = sf::Color::Red;
			}
			collisionColour.a = 100;
			circle.setFillColor(collisionColour);

			target.draw(circle);
		}
		break;
		}
	}
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void SpriteObject::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

bool SpriteObject::CheckColliding(SpriteObject other)
{
	if (!alive || !other.alive)
	{
		return false;
	}
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
		else
		{
			sf::Vector2f nearestPointToCircle = GetCollisionCentre(); //actual circle centre
			sf::FloatRect otherAABB = other.GetAABB();
			//clamp the circle centre to min and max aabb
			nearestPointToCircle.x = fmaxf(otherAABB.left, fminf(nearestPointToCircle.x, otherAABB.left + otherAABB.width));
			nearestPointToCircle.y = fmaxf(otherAABB.top, fminf(nearestPointToCircle.y, otherAABB.top + otherAABB.height));
			sf::Vector2f displacement = nearestPointToCircle - GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = GetCircleColliderRadius();

			return squareDistance <= circleRadius * circleRadius;
		}
	}
	break;
	default:
		break;
	};
}

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

void SpriteObject::HandleCollision(SpriteObject& other)
{
}

sf::Vector2f SpriteObject::GetCollisionDepth(SpriteObject other)
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

void SpriteObject::SetEnumUsed(CollisionType newEnum)
{
	collisionType = newEnum;
}

float SpriteObject::GetHeight()
{
	return sprite.getLocalBounds().height;
}

float SpriteObject::GetWidth()
{
	return sprite.getLocalBounds().width;
}

void SpriteObject::SetAlive(bool newAlive)
{
	alive = newAlive;
}

bool SpriteObject::GetAlive()
{
	return alive;
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width / 2.0f;
	centre.y += bounds.height / 2.0f;

	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;

	return centre;
}

float SpriteObject::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	if (bounds.width > bounds.height)
		return bounds.width / 2.0f;
	else
		return bounds.height / 2.0f;
}

sf::FloatRect SpriteObject::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	sf::Vector2f centre = GetCollisionCentre();

	bounds.left = centre.x - bounds.width / 2.0f;
	bounds.top = centre.y - bounds.height / 2.0f;

	return bounds;
}