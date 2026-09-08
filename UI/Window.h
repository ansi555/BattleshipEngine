#pragma once

#include <SFML/Graphics.hpp>

#include "../Assets/Colors.h"
#include "../Engine/Board.h"
#include "../Engine/GameEngine.h"
#include "BoardRenderer.h"
#include "GameState.h"
#include "MenuRenderer.h"

class Window {
   private:
    sf::RenderWindow window;
    sf::Font font;

    GameEngine engine;
    MenuRenderer menuRenderer;
    BoardRenderer boardRenderer;
    GameState state;
    Board player1Board;
    Board player2Board;

   public:
    Window();

    void run();

   private:
    void handleEvents();
    void update();
    void render();
};
