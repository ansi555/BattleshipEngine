#include "../Assets/Colors.h"

#include "MenuRenderer.h"

void MenuRenderer::init(sf::Font &font)
{
    title.setFont(font);
    title.setString("Battleship Test");
    title.setCharacterSize(40);
    title.setFillColor(Colors::Black());

    boardBtn.setFont(font);
    boardBtn.setString("Zum Spiel (Test)");
    boardBtn.setCharacterSize(25);
    boardBtn.setFillColor(Colors::SuccessGreen());
}

void MenuRenderer::render(sf::RenderWindow &window)
{
    title.setFillColor(Colors::Black());
    title.setPosition(
        window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100
    );
    boardBtn.setFillColor(Colors::SuccessGreen());
    boardBtn.setPosition(
        window.getSize().x / 2 - boardBtn.getGlobalBounds().width / 2, 250
    );
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
