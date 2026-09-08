#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Board.h"
#include "BoardRenderer.h"

class ShipRenderer {
   public:
    void render(sf::RenderWindow& window, Board& board, BoardArea area, bool leftBoard);
};
