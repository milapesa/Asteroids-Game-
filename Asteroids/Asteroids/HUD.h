#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class Player;
class GameLogic;
class GameScene;

class HUD
{
public:
    virtual ~HUD() = default;
    
    virtual void update() {}

    virtual void render(sf::RenderWindow* window) const = 0;

    /** Used for children huds to receive a used input */
    virtual void receiveEvent(const sf::Event& event) {}
};

class PlayerHUD : public HUD
{
private:
    sf::Text scoreText;

    sf::Text waveText;

    GameScene* gameScene = nullptr;

    Player* player = nullptr;

    std::vector<sf::Sprite> playerHearths;

public:
    PlayerHUD(const sf::Font& font, GameScene* inGameScene, Player* inPlayer, const  sf::Vector2f& inOriginPosition);

    /** Updates score and wave text */
    void update() override;

    void render(sf::RenderWindow* window) const override;
};

class GameOverHUD : public HUD
{
private:
    
    Button retryButton;

    Button menuButton;

    sf::Text gameOverText;

    GameLogic* gameLogic = nullptr;

public:
    GameOverHUD(GameLogic* inGameLogic);
    
    void render(sf::RenderWindow* window) const override;

    /** Checks whether the retry or the menu button where selected */
    void receiveEvent(const sf::Event& event) override;
};
