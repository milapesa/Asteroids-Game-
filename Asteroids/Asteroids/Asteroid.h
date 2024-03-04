#pragma once

#include "Actor.h"

class Asteroid : public Actor
{
private:
	int size = 3;

	/** The score the player will gain when destroying this asteroid which is multiplied by the current size */
	float scorePerSize = 100.0f;

	float speed = 500.0f;

protected:
	void setSize(int inSize);

public:
	Asteroid(GameLogic* inGameLogic, const sf::Vector2f& position, float inRotation);
	
	Asteroid(GameLogic* inGameLogic, const sf::Vector2f& position, float inRotation, int inSize);

	void update(float deltaTime) override;
	
	void makeChildAsteroids() const;

	void collidedWith(Actor* OtherActor) override;
};

