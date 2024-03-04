#pragma once

#include "SFML/Graphics.hpp"

class GameLogic;

class Actor
{
protected:
    float rotationSpeed = 0.0f;

    sf::Vector2f velocity;

    sf::Sprite sprite;

    GameLogic* gameLogic = nullptr;

    bool markedForDestroy = false;

public:
    Actor(GameLogic* inGameLogic, const sf::Vector2f& inPosition, const sf::Texture& inTexture);

    virtual ~Actor() = default;

    /** Moves the sprite with the velocity and the rotation speed */
    virtual void update(float deltaTime);

    /** Draws the sprite */
    virtual void render(sf::RenderTarget* target);

    sf::Vector2f getForwardVector() const;

    const sf::Vector2f& getPosition() const { return sprite.getPosition(); }

    void setPosition(const sf::Vector2f& inPosition) { sprite.setPosition(inPosition); }

    const sf::Sprite& getSprite() const { return sprite; }
    
    virtual void collidedWith(Actor* OtherActor) {}

    /** Flags the actor for deletion in a later frame */
    void markForDestroy() { markedForDestroy = true; }

    bool isMarkForDestroy() const { return markedForDestroy; }
};
