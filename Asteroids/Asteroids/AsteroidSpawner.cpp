#include "AsteroidSpawner.h"

#include <SFML/System/Vector2.hpp>
#include "Asteroid.h"
#include "GameLogic.h"
#include "MathUtils.h"
#include "Scene.h"

void AsteroidSpawner::spawn()
{
    const int amountToSpawn = startingAsteroids + currentWave * amountToIncreasePerWave;
    ++currentWave;

    startWaveTime = gameLogic->getCurrentScene()->getPlayTime();
    
    for (int i = 0; i < amountToSpawn; i++)
    {
        Asteroid* newAsteroid = new Asteroid(gameLogic, sf::Vector2f(0.0f, 0.0f), MathUtils::randRange(0.0f, 360.0f));
        
        const sf::FloatRect globalBounds = newAsteroid->getSprite().getGlobalBounds();
        const float minX = -globalBounds.width;
        const float maxX = gameLogic->getWindowWidth() + globalBounds.width;
        const float minY = -globalBounds.height;
        const float maxY = gameLogic->getWindowHeight() + globalBounds.height;

        const float side = MathUtils::randRange(0.0f, 4.0f);
        sf::Vector2f position (MathUtils::randRange(minX, maxX), MathUtils::randRange(minY, maxY));
        if (side < 1.0f)
        {
            position.x = minX;
        }
        else if (side < 2.0f)
        {
            position.y = maxY;
        }
        else if (side < 3.0f)
        {
            position.x = maxX;
        }
        else
        {
            position.y = minY;
        }
        newAsteroid->setPosition(position);
        gameLogic->getCurrentScene()->addActorToScene(newAsteroid);
    } 
}

bool AsteroidSpawner::canSpawn() const
{
    if (gameLogic->getCurrentScene()->getPlayTime() - startWaveTime > timeBetweenWaves)
    {
        return true;
    }

    for (Actor* actor : gameLogic->getCurrentScene()->getActorsInScene())
    {
        if (dynamic_cast<Asteroid*>(actor))
        {
            return false;
        }
    }

    return true;
}
