#include "Scene.h"

#include "CollisionManager.h"
#include "Button.h"
#include "GameLogic.h"
#include "HUD.h"

namespace SceneUtils
{
    constexpr PlayerInput FirstPlayerInput = {
        sf::Keyboard::W,
        sf::Keyboard::S,
        sf::Keyboard::D,
        sf::Keyboard::A,
        sf::Keyboard::Space,
    };

    constexpr PlayerInput SecondPlayerInput = {
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::Right,
        sf::Keyboard::Left,
        sf::Keyboard::Enter,
    };
}

Scene::~Scene()
{
    for (const Actor* actor : actors)
    {
        delete actor;
    }

    for (const Actor* actor : actorsToAdd)
    {
        delete actor;
    }
}

void Scene::update()
{
    // Get the delta time for the game update
    dt = GameClock.restart();
    playTime += dt.asSeconds();

    actors.insert(actors.end(), actorsToAdd.begin(), actorsToAdd.end());
    actorsToAdd.clear();

    for (auto it = actors.begin(); it != actors.end(); )
    {
        Actor* actor = *it;
        if (actor->isMarkForDestroy())
        {
            it = actors.erase(it);
            delete actor;
        }
        else
        {
            actor->update(dt.asSeconds());
            ++it;
        }
    }
}

void Scene::render(sf::RenderWindow* window)
{
    for (Actor* actor : actors)
    {
        actor->render(window);
    }
}

void Scene::addActorToScene(Actor* newActor)
{
    actorsToAdd.push_back(newActor);
}

const std::vector<Actor*>& Scene::getActorsInScene() const
{
    return actors;
}

float Scene::getPlayTime() const
{
    return playTime;
}

void GameScene::removeHUD(HUD* hud)
{
    for (auto it = huds.begin(); it != huds.end();)
    {
        if (*it == hud)
        {
            it = huds.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

GameScene::GameScene(GameLogic* inGameLogic, int quantityOfPlayers)
    :   asteroidSpawner(inGameLogic),
        collisionManager(inGameLogic), gameLogic(inGameLogic)
{
    //Setting the players initial values
    auto addPlayer = [this](const PlayerInput& playerInput, const sf::Vector2f& hudOffset, sf::Vector2f initialPosition, sf::Color inColor)
    {
        Player* player = new Player(getGameLogic(), initialPosition, inColor);
        addActorToScene(player);
        PlayerController playerController (playerInput);
        playerController.setPlayer(player);
        playerControllers.push_back(playerController);
        addHUD(new PlayerHUD(getGameLogic()->getFont(), this, player, hudOffset));
    };
    addPlayer(SceneUtils::FirstPlayerInput, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0,0), sf::Color::White);
    
    if (quantityOfPlayers > 1)
    {
        addPlayer(SceneUtils::SecondPlayerInput, sf::Vector2f(0.0f, inGameLogic->getWindowHeight() - 300.0f), sf::Vector2f(100,0), sf::Color::Cyan);
    }
}

GameScene::~GameScene()
{
    for (const HUD* hud : huds)
    {
        delete hud;
    }
}

void GameScene::update()
{
    if (!gameOver && isGameOver())
    {
        gameOver = true;
        addHUD(new GameOverHUD(gameLogic));
    }

    if (!gameOver)
    {
        Scene::update();

        if (asteroidSpawner.canSpawn())
        {
            asteroidSpawner.spawn();
        }
        collisionManager.checkCollisions();
    }
 
    for (HUD* hud : huds)
    {
        hud->update();
    }
}

bool GameScene::isGameOver() const
{
    for (const PlayerController& playerController : playerControllers)
    {
        if (playerController.getPlayer()->getLifeLeft() <= 0)
        {
            return true;
        }
    }
    return false;
}

void GameScene::render(sf::RenderWindow* window)
{
    Scene::render(window);

    for (const HUD* hud : huds)
    {
        hud->render(window);
    }
}

void GameScene::receiveEvent(const sf::Event& event)
{
    for (PlayerController& playerController : playerControllers)
    {
        playerController.receiveEvent(event);
    }

    for (HUD* hud : huds)
    {
        hud->receiveEvent(event);
    }
}

MainMenuScene::MainMenuScene(GameLogic* inGameLogic)
    : titleText("Asteroids", inGameLogic->getFont(), 100.0f),
        onePlayerButton("One Player", sf::Vector2f(150.0f, 50.0f), 20.0f),
        twoPlayerButton("Two Players", sf::Vector2f(150.0f, 50.0f), 20.0f),
        gameLogic(inGameLogic)
{
    onePlayerButton.setFont(gameLogic->getFont());
    twoPlayerButton.setFont(gameLogic->getFont());
}

void MainMenuScene::render(sf::RenderWindow* window)
{
    Scene::render(window);

    titleText.setPosition(gameLogic->getScreenMiddle(titleText.getGlobalBounds()) - sf::Vector2f(0.0f, 250.0f));
    const sf::Vector2f buttonOffset (200.0f, 0.0f);
    onePlayerButton.setPosition(gameLogic->getScreenMiddle(onePlayerButton.getGlobalBounds()) - buttonOffset);
    twoPlayerButton.setPosition(gameLogic->getScreenMiddle(twoPlayerButton.getGlobalBounds()) + buttonOffset);
    
    window->draw(titleText);
    onePlayerButton.drawTo(*window);
    twoPlayerButton.drawTo(*window);
}

void MainMenuScene::receiveEvent(const sf::Event& event)
{
    Scene::receiveEvent(event);
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if (onePlayerButton.isMouseOver(gameLogic))
        {
            gameLogic->startGame(1);
        }
        else if (twoPlayerButton.isMouseOver(gameLogic))
        {
            gameLogic->startGame(2);
        }
    }
}
