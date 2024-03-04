#include "HUD.h"

#include "GameLogic.h"
#include "Scene.h"

PlayerHUD::PlayerHUD(const sf::Font& font, GameScene* inGameScene, Player* inPlayer, const sf::Vector2f& inOriginPosition)
    : gameScene(inGameScene), player(inPlayer)
{
    //Creating GUI elements
    scoreText = sf::Text("", font, 40);
    waveText = sf::Text("", font, 20.0f);
    
    scoreText.setPosition(sf::Vector2f(96, 14) + inOriginPosition);
    waveText.setPosition(sf::Vector2f(96, 60) + inOriginPosition);

    for (int i = 0; i < player->getLifeLeft(); i++)
    {
        sf::Sprite newSprite;
        newSprite.setTexture(inGameScene->getGameLogic()->getTexture("Assets/lives.png"));
        newSprite.setPosition(sf::Vector2f(66.0f + 55.0f * static_cast<float>(i), 64.0f) + inOriginPosition);
        newSprite.scale(0.05f, 0.05f);
        playerHearths.push_back(newSprite);
    }
}

void PlayerHUD::update()
{
    waveText.setString("Wave: " + std::to_string(gameScene->getAsteroidSpawner().getCurrentWave()));
    const float score = player->getScore();
    scoreText.setString("Score: " + std::to_string(static_cast<int>(score)));
}

void PlayerHUD::render(sf::RenderWindow* window) const
{
    window->draw(scoreText);
    window->draw(waveText);
    for (int i = 0; i < player->getLifeLeft(); i++)
    {
        window->draw(playerHearths[i]);
    }
}

GameOverHUD::GameOverHUD(GameLogic* inGameLogic)
    : retryButton("Try Again?", {200, 50}, 20),
        menuButton("Back to Menu", {200, 50}, 20),
        gameOverText("Game Over", inGameLogic->getFont(), 100), gameLogic(inGameLogic)
{
    //Creating GUI elements
    sf::Vector2f gameOverPosition = inGameLogic->getScreenMiddle(gameOverText.getGlobalBounds());
    gameOverPosition.y -= 150.0f;
    gameOverText.setPosition(gameOverPosition);

    retryButton.setFont(inGameLogic->getFont());
    retryButton.setPosition(inGameLogic->getScreenMiddle(retryButton.getGlobalBounds()));

    menuButton.setFont(inGameLogic->getFont());
    menuButton.setPosition(inGameLogic->getScreenMiddle(menuButton.getGlobalBounds()) + sf::Vector2f(0.0f, 100.0f));
}

void GameOverHUD::render(sf::RenderWindow* window) const
{
    window->draw(gameOverText);
    retryButton.drawTo(*window);
    menuButton.drawTo(*window);
}

void GameOverHUD::receiveEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (retryButton.isMouseOver(gameLogic))
        {
            gameLogic->restartGame();
        }
        else if (menuButton.isMouseOver(gameLogic))
        {
            gameLogic->backToMenu();
        }
    }
}

