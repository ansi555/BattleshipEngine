#pragma once

#include <SFML/Graphics.hpp>

#include "../Assets/Colors.h"
#include "../Engine/GameEngine.h"

class Window
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;

    GameEngine engine;

public:
    Window();

    void run();

private:
    void handleEvents();
    void update();
    void render();
};
