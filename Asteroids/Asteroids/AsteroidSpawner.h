#pragma once

class GameLogic;

class AsteroidSpawner
{
private:
    int startingAsteroids = 1;

    int amountToIncreasePerWave = 1;

    float timeBetweenWaves = 20.0f;

    int currentWave = 0;
    
    GameLogic* gameLogic = nullptr;

    /** The time that last wave started */
    float startWaveTime = 0.0f;

public:
    //Functions
    AsteroidSpawner(GameLogic* inGameLogic) : gameLogic(inGameLogic) {}
    
    void spawn();

    bool canSpawn() const;

    int getCurrentWave() const { return currentWave; }
};
