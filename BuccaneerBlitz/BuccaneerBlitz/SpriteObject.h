#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SpriteObject
{
public:

	SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	void SetSpriteScale(float xScale, float yScale);
	float GetHeight();
	float GetWidth();

	void SetAlive(bool newAlive);
	bool GetAlive();
	int GetLives();
	void ModifyLives(int lifeValue);

protected:

	sf::Sprite sprite;
	sf::Sound sound;

	sf::Vector2f position;
	bool alive;
	int lives;
};

