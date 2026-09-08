#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Board.h"

class BoardRenderer {
   private:
    sf::Text player1BoardLabel;
    sf::Text player2BoardLabel;

   public:
    void init(sf::Font& font);

    void render(sf::RenderWindow& window, Board& board, bool leftBoard);
};
