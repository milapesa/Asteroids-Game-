#include "Bullet.h"

#include "GameLogic.h"

Bullet::Bullet(GameLogic* inGameLogic, Player* inShotBy, const sf::Vector2f& inPosition, float rotation)
	: Actor(inGameLogic, inPosition, inGameLogic->getTexture("Assets/bullet.png")), shotBy(inShotBy)
{
	sprite.setScale(0.4f, 0.4f);
	sprite.setRotation(rotation);
	velocity = getForwardVector() * speed;
}

void Bullet::update(float deltaTime)
{
	Actor::update(deltaTime);

	const sf::Vector2f&  position = getPosition();
	bool outOfBounds = position.x < 0.0f || position.x > gameLogic->getWindowWidth();
	outOfBounds |= position.y < 0.0f || position.y > gameLogic->getWindowHeight();
	
	if (outOfBounds)
	{
		markForDestroy();
	}
}


