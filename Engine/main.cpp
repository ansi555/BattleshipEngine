#include "GameEngine.h"
#include <SFML/Graphics.hpp>

int main()
{
    GameEngine engine;

    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Battleship");

    sf::Font font;
    font.loadFromFile("assets/DejaVuSans.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setPosition(50, 50);

    if (engine.isRunning())
    {
        text.setString("BattleshipEngine running!");
    }
    else
    {
        text.setString("Fehler 404");
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(text);
        window.display();
    }
    return 0;
}
