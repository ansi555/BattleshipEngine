#include "../Assets/Colors.h"

#include "MenuRenderer.h"

void MenuRenderer::init(sf::Font &font)
{
    title.setFont(font);
    title.setString("Battleship Test");
    title.setCharacterSize(40);
    title.setFillColor(Colors::Black);
    title.setPosition(250, 100);

    boardBtn.setFont(font);
    boardBtn.setString("Zum Spiel (Test)");
    boardBtn.setCharacterSize(25);
    boardBtn.setFillColor(Colors::DarkGreen);
    boardBtn.setPosition(300, 250);
}

void MenuRenderer::render(sf::RenderWindow &window)
{
    window.draw(title);
    window.draw(boardBtn);
}

bool MenuRenderer::isTestBoardClicked(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    return boardBtn.getGlobalBounds().contains(
        mousePos.x,
        mousePos.y);
}
