#include "Asteroid.h"
#include "GameLogic.h"
#include "Bullet.h"
#include "MathUtils.h"
#include "Player.h"
#include "Scene.h"

Asteroid::Asteroid(GameLogic* inGameLogic, const sf::Vector2f& position, float inRotation)
    : Actor(inGameLogic, position, inGameLogic->getTexture("Assets/asteroid.png"))
{
    setSize(size);
    sprite.setRotation(inRotation);
    velocity = getForwardVector() * speed;
}

void Asteroid::setSize(int inSize)
{
    size = inSize;
    const float newScale = static_cast<float>(size) * 0.5f;
    sprite.setScale(newScale, newScale);
}

Asteroid::Asteroid(GameLogic* inGameLogic, const sf::Vector2f& position, float inRotation, int inSize)
    : Asteroid(inGameLogic, position, inRotation)
{
    setSize(inSize);
}

void Asteroid::update(float deltaTime)
{
    Actor::update(deltaTime);

    gameLogic->warpSpritePosition(sprite, false);
}

void Asteroid::makeChildAsteroids() const
{
    if (size == 1)
    {
        return;
    }
    for (int i = 0; i < 2; ++i)
    {
        const float newRotation = MathUtils::randRange(sprite.getRotation() - 60, sprite.getRotation() + 60);
        gameLogic->getCurrentScene()->addActorToScene(new Asteroid(gameLogic, getPosition(), newRotation, size - 1));
    }
}

void Asteroid::collidedWith(Actor* OtherActor)
{
    if (const Bullet* bullet = dynamic_cast<Bullet*>(OtherActor))
    {
        Player* player = bullet->getShotBy();
        player->addScore(scorePerSize * static_cast<float>(size));
        
        markForDestroy();
        OtherActor->markForDestroy();
        
        makeChildAsteroids();
    }
    else if (auto* currentPlayer = dynamic_cast<Player*>(OtherActor))
    {
        currentPlayer->takeDamage(1);
        makeChildAsteroids();
        markForDestroy();
    }
}
