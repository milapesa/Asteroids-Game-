#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class Scene;

/**
	Wrapper class that acts as game engine.
 */
class GameLogic
{
private:
	
	sf::Event event;
	
	sf::VideoMode videoMode;
	
	sf::RenderWindow* window;
	
	sf::Font font;

	std::map<std::string, sf::Texture*> textures;
	
	sf::Sprite gameBackground;
	
	Scene* currentScene = nullptr;
	
	bool restartGameRequested = false;

	int quantityOfPlayers = 0;

public:
	GameLogic();

	virtual ~GameLogic();

	bool isWindowOpen() const;

	/** Sends the user input to the current scene */
	void pollEvents();

	/** Updates the current scene */
	void update();

	/** Renders the current scene */
	void render() const;

	/** Starts the GameScene */
	void startGame(int inQuantityOfPlayers);

	/** Starts the MainMenuScene */
	void backToMenu();

	/** Re-creates the GameScene on the next tick */
	void restartGame() { restartGameRequested = true;}

	/** Warps objects so they dont go off screen */
	void warpSpritePosition(sf::Sprite& sprite, bool alwaysOnScreen) const;

	/** Renders objects multiple times when near the screen */
	void warpSpriteRender(const sf::Sprite& sprite, sf::RenderTarget* target) const;

	Scene* getCurrentScene() const { return currentScene; }

	float getWindowHeight() const { return static_cast<float>(videoMode.height); }
	
	float getWindowWidth() const { return static_cast<float>(videoMode.width); }

	sf::Vector2i getMousePosition() const;

	const sf::Font& getFont() const { return font; }

	sf::Vector2f getScreenMiddle(const sf::FloatRect& bounds) const;

	const sf::Texture& getTexture(const std::string& fileName);
};

