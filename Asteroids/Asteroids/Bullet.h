#pragma once

#include "SFML/Graphics.hpp"
#include "Actor.h"

class Player;
class GameLogic;

class Bullet : public Actor
{
private:
	/** The player that shot this bullet */
	Player* shotBy = nullptr;

	float speed = 1000.0f;

public:
	Bullet(GameLogic* inGameLogic, Player* inShotBy, const sf::Vector2f& inPosition, float rotation);

	/** Destroys the bullet when out of the screen */
	void update(float deltaTime) override;

	Player* getShotBy() const { return shotBy; }
};

