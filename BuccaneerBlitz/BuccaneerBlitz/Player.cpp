#include "Player.h"
#include "AssetManager.h"
#include "LevelScreen.h"

enum class PhysicsType
{
	VELOCITY_VERLET
};

Player::Player(sf::RenderWindow* newWindow, LevelScreen* newLevelScreen)
	: PhysicsObject()
	, window(newWindow)
	, levelScreen(newLevelScreen)
	, cooldownTimer()
	, cooldown(1.0f)
	, hasAnchor(false)
	, hasMultiFire(false)
	, attackSound()
	, pickupSound()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Player/cf_Player1_PNG.png"));
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	collisionScale = sf::Vector2f(0.45f, 0.95f);

	lives = 3;
	hasDrag = true;

	attackSound.setBuffer(AssetManager::RequestSoundBuffer("Assets/Sounds/522209__kutejnikov__explosion.wav"));
	attackSound.setVolume(50.0f);

	pickupSound.setBuffer(AssetManager::RequestSoundBuffer("Assets/Sounds/253172__suntemple__retro-bonus-pickup-sfx.wav"));
	attackSound.setVolume(50.0f);
}

void Player::Update(sf::Time frameTime)
{
	PhysicsObject::Update(frameTime);

	//checks to see if input is pressed while currenly possessing anchor
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && hasAnchor == true)
	{
		FireAnchor(cooldown);
	}
	//checks to see if input is pressed while currenly possessing multifire
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && hasMultiFire == true)
	{
		FireMultiFire(cooldown);
	}
	//checks to see if input is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		FireCannonBall(cooldown);
	}

}

void Player::HandleCollision(PhysicsObject& other)
{
	if (typeid(other).name() == typeid(AnchorPickup).name())
	{
		pickupSound.play();
		hasAnchor = true;
	}
	if (typeid(other).name() == typeid(MultiFirePickup).name())
	{
		pickupSound.play();
		hasMultiFire = true;
	}
	if (typeid(other).name() == typeid(LifePickup).name())
	{
		pickupSound.play();
	}
	else
	{
		sf::Vector2f depth = GetCollisionDepth(other);
		sf::Vector2f newPosition = GetPosition();

		if (abs(depth.x) < abs(depth.y))
		{
			//move in x direction
			newPosition.x += depth.x;
			velocity.x = 0;
			acceleration.x = 0;
		}
		else
		{
			//move in y direction
			newPosition.y += depth.y;
			velocity.x = 0;
			acceleration.x = 0;
		}

		SetPosition(newPosition);
	}
}

void Player::FireCannonBall(float newCooldown)
{
	//checks if timer is more than cooldown
	if (cooldownTimer.getElapsedTime().asSeconds() > newCooldown)
	{
		attackSound.play();
		//spawns cannonball on screen
		levelScreen->SpawnProjectile(Projectile::CANNONBALL, *this);
		//restarts cooldown to avoid multiple spawns
		cooldownTimer.restart();
	}
}

void Player::FireAnchor(float newCooldown)
{
	if (cooldownTimer.getElapsedTime().asSeconds() > newCooldown)
	{
		attackSound.play();
		//spawns anchor on screen
		levelScreen->SpawnProjectile(Projectile::ANCHOR, *this);
		//sets to false to only allow one fire per item
		hasAnchor = false;
		//restarts cooldown to avoid multiple spawns
		cooldownTimer.restart();
	}
}

void Player::FireMultiFire(float newCooldown)
{
	if (cooldownTimer.getElapsedTime().asSeconds() > newCooldown)
	{
		attackSound.play();
		//spawns cannonballs on screen
		levelScreen->SpawnProjectile(Projectile::MULTIFIRE, *this);
		//sets to false to only allow one fire per item
		hasMultiFire = false;
		//restarts cooldown to avoid multiple spawns
		cooldownTimer.restart();
	}
}

bool Player::GetHasAnchor()
{
	return hasAnchor;
}

bool Player::GetHasMultiFire()
{
	return hasMultiFire;
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 10000;

	sf::Vector2f pos = sprite.getPosition();
	float spriteBottom = pos.y + sprite.getGlobalBounds().height;

	acceleration.x = 0;
	acceleration.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//changes x direction to go right
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//changes x direction to go left
		acceleration.x = ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getPosition().y > 0)
	{
		//changes y direction to go up
		acceleration.y = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && spriteBottom < window->getSize().y)
	{
		//changes y direction to go down
		acceleration.y = ACCEL;
	}
}
