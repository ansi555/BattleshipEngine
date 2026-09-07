#include "window.h"

Window::Window()
{
    window.create(
        sf::VideoMode(800, 600),
        "BattleshipGame");

    font.loadFromFile("Assets/DejaVuSans.ttf");

    text.setFont(font);
    text.setFillColor(Colors::Black);
    text.setCharacterSize(30);
    text.setPosition(50, 50);
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
    }
}

void Window::update()
{
    if (engine.isRunning())
    {
        text.setString("BattleshipEngine running!");
    }
    else
    {
        text.setString("Fehler 404");
    }
}

void Window::render()
{
    window.clear(Colors::Menu);
    window.draw(text);
    window.display();
}
