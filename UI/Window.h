#pragma once

#include <SFML/Graphics.hpp>

#include "../Assets/Colors.h"
#include "../Engine/Board.h"
#include "../Engine/GameEngine.h"
#include "../Engine/Player.h"
#include "BoardRenderer.h"
#include "GameState.h"
#include "MenuRenderer.h"
#include "ShipRenderer.h"

class Window {
   private:
    sf::RenderWindow window;
    sf::Font font;
    sf::RectangleShape darkModeButton;
    sf::Text darkModeButtonLabel;

    GameEngine engine;
    MenuRenderer menuRenderer;
    BoardRenderer boardRenderer;
    ShipRenderer shipRenderer;
    GameState state;

    Board player1Board;
    Board player2Board;

    Player player1;
    Player player2;

    void handleEvents();
    void update();
    void render();
    void renderBackground();
    void renderDarkModeButton();
    bool isDarkModeButtonClicked() const;

   public:
    Window();

    void run();
    void resetGame();
    void initGame();

    std::string winner;
};
