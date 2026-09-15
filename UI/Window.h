#pragma once

#include <SFML/Graphics.hpp>

#include "../Assets/Colors.h"
#include "../Engine/Board.h"
#include "../Engine/GameEngine.h"
#include "BoardRenderer.h"
#include "GameState.h"
#include "MenuRenderer.h"
#include "ShipRenderer.h"

class Window {
   private:
    sf::RenderWindow window;
    sf::Font font;

    GameEngine engine;
    MenuRenderer menuRenderer;
    BoardRenderer boardRenderer;
    ShipRenderer shipRenderer;
    GameState state;

    Board player1Board;
    Board player2Board;

    void handleEvents();
    void update();
    void render();

   public:
    Window();

    void run();
    void resetGame();
    void initGame();

    std::string winner;
};
