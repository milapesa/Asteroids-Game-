#include "CollisionManager.h"
#include "Actor.h"
#include "GameLogic.h"
#include "Scene.h"

void CollisionManager::checkCollisions() const
{
     const std::vector<Actor*>& actors = gameLogic->getCurrentScene()->getActorsInScene();
     
     for (auto outerIt = actors.begin(); outerIt != actors.end(); ++outerIt)
     {
          for (auto innerIt = outerIt + 1; innerIt != actors.end(); ++innerIt)
          {
               if (*outerIt == *innerIt)
               {
                    continue;
               }

               sf::FloatRect outerBounds = (*outerIt)->getSprite().getGlobalBounds();
               sf::FloatRect innerBounds = (*innerIt)->getSprite().getGlobalBounds();
               
               if (outerBounds.intersects(innerBounds) || innerBounds.intersects(outerBounds))
               {
                    (*outerIt)->collidedWith(*innerIt);
                    (*innerIt)->collidedWith(*outerIt);
               }
          }
     }
}
