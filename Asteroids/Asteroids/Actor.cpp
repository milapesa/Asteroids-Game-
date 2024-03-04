#include "Actor.h"

#include "GameLogic.h"
#include "MathUtils.h"

namespace ActorUtils
{
    const sf::Vector2f UP_VECTOR = sf::Vector2f(0.0f, -1.0f);
}

Actor::Actor(GameLogic* inGameLogic, const sf::Vector2f& inPosition, const sf::Texture& inTexture)
    : sprite(inTexture), gameLogic(inGameLogic)
{
    const sf::Vector2u textureSize = sprite.getTexture()->getSize();
    sprite.setOrigin(static_cast<float>(textureSize.x) / 2.0f, static_cast<float>(textureSize.y) / 2.0f);
    sprite.setPosition(inPosition);
}

void Actor::update(float deltaTime)
{
    sprite.rotate(rotationSpeed * deltaTime);
    sprite.move(velocity * deltaTime);
}

void Actor::render(sf::RenderTarget* target)
{
    target->draw(sprite);
}

sf::Vector2f Actor::getForwardVector() const
{
    return MathUtils::rot(ActorUtils::UP_VECTOR, sprite.getRotation());
}

