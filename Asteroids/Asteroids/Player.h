#pragma once

#include "Actor.h"

class Bullet;

class Player : public Actor
{
private:

    /** How much the player will rotate when receiving the turn input */
    float inputRotationSpeed = 200.0f;

    /** How much the player will accelerate when receiving the thrust input */
    float inputThrust;

    /** How much the velocity will increase in the forward vector direction */
    float speed = 500.0f;

    /** Position from where the bullet will spawn */
    sf::Vector2f shootPosition = sf::Vector2f(85.0f, -40.0f);

    float timeBetweenShoots = 0.1f;

    float lastShotTime = 0.0f;

    int lives = 3;
    
    float lastDamageTime = -1.0f;

    float gracePeriod = 1.0f;

    /** Used to blink the player sprite during the grace period */
    float invisibleGraceTime = 0.1f;

    float score = 0.0f;

    sf::Vector2f initialLocationOffset;

    void centerPlayer();

    /** Whether the player cannot take damage */
    bool inGrace() const;

public:
    Player(GameLogic* inGameLogic, sf::Vector2f inInitialLocationOffset, sf::Color inColor);

    /** Warps the player position */
    void update(float deltaTime) override;

    /** Warps the player sprite and blinks the sprite on grace period */
    void render(sf::RenderTarget* target) override;

    /** Rotates the player */
    void turn(float turnForce);

    void thrust(float thrust);

    bool canShoot() const;

    Bullet* shoot();

    void takeDamage(int damage);

    int getLifeLeft() const;

    GameLogic* getGameLogic() const { return gameLogic; }

    float getScore() const { return score; }

    void addScore(float inScore) { score += inScore; }
};

struct PlayerInput
{
    sf::Keyboard::Key thrustUp;
    sf::Keyboard::Key thrustDown;
    sf::Keyboard::Key turnClockwise;
    sf::Keyboard::Key turnAntiClockwise;
    sf::Keyboard::Key shoot;
};

class PlayerController
{
private:
    Player* player = nullptr;

    PlayerInput playerInput;

public:
    PlayerController(const PlayerInput& inPlayerInput) : playerInput(inPlayerInput) {}

    /** Moves the player checking the pressed inputs */
    void receiveEvent(const sf::Event& event) const;

    void setPlayer(Player* inPlayer) { player = inPlayer; }
    
    Player* getPlayer() const { return player; }
};
