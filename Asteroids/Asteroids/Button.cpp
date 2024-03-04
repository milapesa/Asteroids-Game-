#include "Button.h"

#include "GameLogic.h"

Button::Button(std::string inText, sf::Vector2f size, int charSize)
{
    text.setString(inText);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::Black);
    button.setSize(size);
}

void Button::setFont(const sf::Font& inFont)
{
    text.setFont(inFont);
}

void Button::setPosition(sf::Vector2f inPosition)
{
    button.setPosition(inPosition);

    const float xPosition = inPosition.x + button.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2;
    const float yPosition = inPosition.y + button.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2 - 5.0f;

    text.setPosition(xPosition, yPosition);
}

void Button::drawTo(sf::RenderWindow& window) const
{
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(GameLogic* gameLogic) const
{
    const float mouseX = static_cast<float>(gameLogic->getMousePosition().x);
    const float mouseY = static_cast<float>(gameLogic->getMousePosition().y);

    const float buttonPositionX = button.getPosition().x;
    const float buttonPositionY = button.getPosition().y;

    const float buttonPositionWidth = buttonPositionX + button.getLocalBounds().width;
    const float buttonPositionHeight = buttonPositionY + button.getLocalBounds().height;

    if (mouseX < buttonPositionWidth && mouseX > buttonPositionX && mouseY < buttonPositionHeight && mouseY > buttonPositionY)
    {
        return true;
    }
    
    return false;
}

sf::FloatRect Button::getGlobalBounds() const
{
    return button.getGlobalBounds();
}
