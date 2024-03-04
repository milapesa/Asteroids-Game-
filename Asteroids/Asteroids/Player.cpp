#include "Player.h"
#include "GameLogic.h"
#include "Bullet.h"
#include "MathUtils.h"
#include "Scene.h"

Player::Player(GameLogic* inGameLogic, sf::Vector2f inInitialLocationOffset, sf::Color inColor)
    : Actor(inGameLogic, sf::Vector2f(0.0f, 0.0f), inGameLogic->getTexture("Assets/Ship.png"))
{
    sprite.setScale(0.5, 0.5);
    initialLocationOffset = inInitialLocationOffset;
    centerPlayer();
    sprite.setColor(inColor);
}

void Player::turn(float turnForce)
{
    rotationSpeed = turnForce * inputRotationSpeed;
}

void Player::thrust(float thrust)
{
    inputThrust = thrust * speed;
}

void Player::update(float deltaTime)
{
    velocity = inputThrust * getForwardVector();

    Actor::update(deltaTime);
    
    gameLogic->warpSpritePosition(sprite, true);
}

void Player::render(sf::RenderTarget* target)
{
    if (lives <= 0)
    {
        // hide player on game over screen
        return;
    }

    if (inGrace())
    {
        // Makes the sprite blink during grace period
        const float timePerTurn = invisibleGraceTime * 2.0f / gracePeriod;
        const int quantityOfTurns = static_cast<int>(gracePeriod / timePerTurn);
        const float timePast = gameLogic->getCurrentScene()->getPlayTime() - lastDamageTime;
        const int turnsRemaining = quantityOfTurns - static_cast<int>(timePast / timePerTurn);
        if (turnsRemaining % 2 == 0)
        {
            return;
        }
    }
    
    Actor::render(target);

    gameLogic->warpSpriteRender(sprite, target);
}

bool Player::canShoot() const
{
    return gameLogic->getCurrentScene()->getPlayTime() - lastShotTime > timeBetweenShoots;
}

Bullet* Player::shoot()
{
    lastShotTime = gameLogic->getCurrentScene()->getPlayTime();

    const sf::Vector2f shootPositionTransformed = sprite.getTransform().transformPoint(shootPosition);
    return new Bullet(gameLogic, this, shootPositionTransformed, sprite.getRotation());
}

void Player::takeDamage(int damage)
{
    if (inGrace())
    {
        return;
    }
    
    lastDamageTime = gameLogic->getCurrentScene()->getPlayTime();
    lives -= damage;
    centerPlayer();
}

int Player::getLifeLeft() const
{
    return lives;
}

void Player::centerPlayer()
{
    setPosition(sf::Vector2f(gameLogic->getWindowWidth() / 2.0f + initialLocationOffset.x, gameLogic->getWindowHeight() / 2.0f + initialLocationOffset.y));
}

bool Player::inGrace() const
{
    if (lastDamageTime <= 0) return false;
    const float playTime = gameLogic->getCurrentScene()->getPlayTime();
    return playTime - lastDamageTime < gracePeriod;
}

void PlayerController::receiveEvent(const sf::Event& event) const
{
    float playerSpeed = 0.0f;
    float playerRotation = 0.0f;
    
    // Player Movement
    if (sf::Keyboard::isKeyPressed(playerInput.turnClockwise))
    {
        playerRotation = 1;
    }
    if (sf::Keyboard::isKeyPressed(playerInput.turnAntiClockwise))
    {
        playerRotation = -1;
    }
        
    if (sf::Keyboard::isKeyPressed(playerInput.thrustUp))
    {
        playerSpeed = 1;
    }
    if (sf::Keyboard::isKeyPressed(playerInput.thrustDown))
    {
        playerSpeed = -1;
    }

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == playerInput.turnClockwise || event.key.code == playerInput.turnAntiClockwise)
        {
            playerRotation = 0;
        }
        if (event.key.code == playerInput.thrustUp || event.key.code ==playerInput.thrustDown)
        {
            playerSpeed = 0;
        }
    }

    player->thrust(playerSpeed);
    player->turn(playerRotation);

    //Bullet Generation
    if (sf::Keyboard::isKeyPressed(playerInput.shoot) && player->canShoot())
    {
        player->getGameLogic()->getCurrentScene()->addActorToScene(player->shoot());
    }
}

