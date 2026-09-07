#pragma once

#include "../Assets/Colors.h"
#include <SFML/Graphics.hpp>

#include "../Engine/Board.h"
#include "../Engine/GameEngine.h"
#include "BoardRenderer.h"
#include "GameState.h"
#include "MenuRenderer.h"

class Window
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text playerBoardLabel;
    sf::Text enemyBoardLabel;

    GameEngine engine;
    MenuRenderer menuRenderer;
    BoardRenderer boardRenderer;
    GameState state;
    Board playerBoard;
    Board enemyBoard;

public:
    Window();

    void run();

private:
    void handleEvents();
    void update();
    void render();
};
