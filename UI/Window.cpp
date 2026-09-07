#include "Window.h"

Window::Window()
{
    window.create(sf::VideoMode(1200, 800), "BattleshipGame");

    state = MENU;
    font.loadFromFile("Assets/DejaVuSans.ttf");

    menuRenderer.init(font);

    playerBoardLabel.setFont(font);
    playerBoardLabel.setString("Eigenes Board");
    playerBoardLabel.setCharacterSize(24);
    playerBoardLabel.setFillColor(Colors::Black);
    playerBoardLabel.setPosition(120, 50);

    enemyBoardLabel.setFont(font);
    enemyBoardLabel.setString("Gegner-Board");
    enemyBoardLabel.setCharacterSize(24);
    enemyBoardLabel.setFillColor(Colors::Black);
    enemyBoardLabel.setPosition(520, 50);
}

void Window::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Window::handleEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (state == MENU)
            {
                if (menuRenderer.isTestBoardClicked(window))
                {
                    state = BOARD;
                }
            }
        }
    }
}

void Window::update()
{
}

void Window::render()
{
    window.clear(Colors::Menu);

    if (state == MENU)
    {
        menuRenderer.render(window);
    }

    if (state == BOARD)
    {
        window.draw(playerBoardLabel);
        window.draw(enemyBoardLabel);

        boardRenderer.render(window, playerBoard, 50, 100);
        boardRenderer.render(window, enemyBoard, 450, 100);
    }

    window.display();
}
