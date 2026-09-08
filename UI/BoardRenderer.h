#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Board.h"

class BoardRenderer {
   private:
    sf::Text player1BoardLabel;
    sf::Text player2BoardLabel;

    sf::Text rowLabels[15];
    sf::Text columnLabels[15];

   public:
    void init(sf::Font& font);

    void render(sf::RenderWindow& window, Board& board, bool leftBoard);
};
