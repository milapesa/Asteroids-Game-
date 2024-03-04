#pragma once

#include "AsteroidSpawner.h"
#include "Button.h"
#include "CollisionManager.h"
#include "Player.h"

class HUD;

/** Base scene that contains actors and renders them */
class Scene
{
private:
    sf::Clock GameClock;
    
    sf::Time dt;

    /** The duration this is running */
    float playTime = 0.0f;

    /** Actors present in the scene */
    std::vector<Actor*> actors;

    /** Actors that are pending to be added into the scene */
    std::vector<Actor*> actorsToAdd;

public:
    virtual ~Scene();

    /** Updates the actors within this scene and deletes the ones mark for destroy */
    virtual void update();

    /** Renders the actors within this scene */
    virtual void render(sf::RenderWindow* window);

    /** Used for children scenes to receive sfml events */
    virtual void receiveEvent(const sf::Event& event) {}

    /** Add actors from the vector to the current scene */
    void addActorToScene(Actor* newActor);

    const std::vector<Actor*>& getActorsInScene() const;

    float getPlayTime() const;
};

class GameScene : public Scene
{

private:
    AsteroidSpawner asteroidSpawner;
	
    CollisionManager collisionManager;

    std::vector<PlayerController> playerControllers;

    GameLogic* gameLogic = nullptr;

    std::vector<HUD*> huds;

    /** Whether the game has finished */
    bool gameOver = false;

protected:
    void addHUD(HUD* newHUD) { huds.push_back(newHUD); }

    void removeHUD(HUD* hud);

    bool isGameOver() const;

public:
    GameScene(GameLogic* inGameLogic, int quantityOfPlayers);

    ~GameScene() override;

    /** Updates the huds, checks collisions and spawns asteroids */
    void update() override;

    /** Renders the huds */
    void render(sf::RenderWindow* window) override;

    /** Sends the input to the players controllers and to the huds */
    void receiveEvent(const sf::Event& event) override;

    AsteroidSpawner getAsteroidSpawner() const { return asteroidSpawner;}

    GameLogic* getGameLogic() const { return gameLogic; }
};

class MainMenuScene : public Scene
{
private:
    sf::Text titleText;
    
    Button onePlayerButton;
    
    Button twoPlayerButton;

    GameLogic* gameLogic = nullptr;

public:
    MainMenuScene(GameLogic* inGameLogic);

    void render(sf::RenderWindow* window) override;

    /** Checks if any of the buttons are clicked */
    void receiveEvent(const sf::Event& event) override;
};