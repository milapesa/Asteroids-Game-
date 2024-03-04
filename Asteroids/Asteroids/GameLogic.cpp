#include "GameLogic.h"

#include "Bullet.h"
#include "Scene.h"

GameLogic::GameLogic()
    : videoMode(sf::VideoMode::getDesktopMode()),
      window(new sf::RenderWindow(videoMode, "LHG Code Exercise"))
{
    srand(time(nullptr));

    currentScene = new MainMenuScene(this);
    font.loadFromFile("Assets/Games.ttf");
    const sf::Texture& backgroundTexture = getTexture("Assets/background.png");
    gameBackground.setTexture(backgroundTexture);
    const float backgroundX = static_cast<float>(backgroundTexture.getSize().x);
    const float backgroundY = static_cast<float>(backgroundTexture.getSize().y);
    gameBackground.setScale(getWindowWidth() / backgroundX,  getWindowHeight() / backgroundY);
}

GameLogic::~GameLogic() 
{
	delete window;

	for (const auto &texture : textures)
	{
        delete texture.second;
	}

    delete currentScene;
}

bool GameLogic::isWindowOpen() const
{
	return window->isOpen();
}

void GameLogic::warpSpritePosition(sf::Sprite& sprite, bool alwaysOnScreen) const
{
    const float currentWidth = static_cast<float>(videoMode.width);
    const float currentHeight = static_cast<float>(videoMode.height);

    sf::Vector2f position = sprite.getPosition();
    const sf::FloatRect globalBounds = sprite.getGlobalBounds();

    const float width = alwaysOnScreen ? 0.0f : globalBounds.width / 2.0f;
    const float height =  alwaysOnScreen ? 0.0f : globalBounds.height / 2.0f;

    if (position.x < 0.0f - width)
    {
        position.x = currentWidth + width;
    }
    else if (position.x > currentWidth + width)
    {
        position.x = 0.0f - width;
    }

    if (position.y < 0.0f - height)
    {
        position.y = currentHeight + height;
    }
    else if (position.y > currentHeight + height)
    {
        position.y = 0.0f - height;
    }
    sprite.setPosition(position);
}

void GameLogic::warpSpriteRender(const sf::Sprite& sprite, sf::RenderTarget* target) const
{
    const sf::Vector2f& position = sprite.getPosition();
    const float height = getWindowHeight();
    const float width = getWindowWidth();
    const sf::FloatRect bounds = sprite.getGlobalBounds();
    const float spriteHeight = bounds.height / 2.0f;
    const float spriteWidth = bounds.width / 2.0f;

    auto drawSprite = [target, &sprite](float x, float y)
    {
        sf::Sprite newSprite = sprite;
        newSprite.setPosition(x, y);
        target->draw(newSprite);
    };
    
    if (position.y + spriteHeight > height)
    {
        drawSprite(position.x, position.y - height);
    }
    else if (position.y - spriteHeight < 0.0f)
    {
        drawSprite(position.x, position.y + height);
    }

    if (position.x + spriteWidth > width)
    {
        drawSprite(position.x - width, position.y);
    }
    else if (position.x - spriteWidth < 0.0f)
    {
        drawSprite(position.x + width, position.y);
    }
}

sf::Vector2i GameLogic::getMousePosition() const
{
    return sf::Mouse::getPosition(*window);
}

sf::Vector2f GameLogic::getScreenMiddle(const sf::FloatRect& bounds) const
{
    return {getWindowWidth() / 2.0f - bounds.width / 2.0f, getWindowHeight() / 2.0f - bounds.height / 2.0f};
}

void GameLogic::startGame(int inQuantityOfPlayers)
{
    quantityOfPlayers = inQuantityOfPlayers;
    delete currentScene;
    currentScene = new GameScene(this, inQuantityOfPlayers);
}

void GameLogic::backToMenu()
{
    delete currentScene;
    currentScene = new MainMenuScene(this);
}

void GameLogic::pollEvents()
{
    // Poll for window being closed
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        currentScene->receiveEvent(event);
    }
}

void GameLogic::update()
{
    pollEvents();

    if (restartGameRequested)
    {
        delete currentScene;
        currentScene = new GameScene(this, quantityOfPlayers);
        restartGameRequested = false;
    }

    currentScene->update();
}

void GameLogic::render() const
{
    // Reset the window
    window->clear();
    window->draw(gameBackground);
    currentScene->render(window);
    window->display();
}

const sf::Texture& GameLogic::getTexture(const std::string& fileName)
{
    const auto it = textures.find(fileName);
    if (it == textures.end())
    {
        textures[fileName] = new sf::Texture();
        textures[fileName]->loadFromFile(fileName);
        return *textures[fileName];
    }
    return *textures[fileName];
}
