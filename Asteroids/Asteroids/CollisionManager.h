#pragma once

class GameLogic;

class CollisionManager
{

protected:
    GameLogic* gameLogic = nullptr;
    
public:
    CollisionManager(GameLogic* inGameLogic) : gameLogic(inGameLogic) {}
    
    void checkCollisions() const;
};
