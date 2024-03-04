#pragma once
#include "SFML/Graphics.hpp"

class GameLogic;

class Button
{
private:
    sf::RectangleShape button;

    sf::Text text;
    
public:
    Button(std::string inText, sf::Vector2f size, int charSize);

    void setFont(const sf::Font &inFont);

    void setPosition(sf::Vector2f inPosition);

    /** Draws the sfml button and the text */
    void drawTo(sf::RenderWindow& window) const;

    /** Returns where the mouse position is inside the bounds of the button */
    bool isMouseOver(GameLogic* gameLogic) const;

    sf::FloatRect getGlobalBounds() const;
};
