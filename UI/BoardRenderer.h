#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Board.h"

class BoardRenderer
{
public:
    void render(
        sf::RenderWindow &window,
        Board &board,
        int startX,
        int startY);
};
