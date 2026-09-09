#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Board.h"
#include "BoardRenderer.h"

class ShipRenderer {
   private:
    Board player1Board;
    Board player2Board;

   public:
    void init(sf::Font& font);
    void render(sf::RenderWindow& window, Board& board, BoardArea area, bool leftBoard);
};
