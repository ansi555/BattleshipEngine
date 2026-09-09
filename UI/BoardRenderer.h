#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Board.h"

struct BoardArea {
    int x;
    int y;
    int width;
    int height;
};

class BoardRenderer {
   private:
    sf::Text player1BoardLabel;
    sf::Text player2BoardLabel;

    sf::Text rowLabels[10];
    sf::Text columnLabels[10];

    sf::Text fleetInfoLabel;
    sf::Text readyLabel;

    sf::RectangleShape backBtn;
    sf::Text backBtnLabel;

   public:
    void init(sf::Font& font);

    Coordinate getClickedCell(sf::RenderWindow& window, Board& board, bool leftBoard);

    void render(sf::RenderWindow& window, Board& board, bool leftBoard, bool showPlacementInfo);

    BoardArea getBoardArea(sf::RenderWindow& window, Board& board, bool leftBoard);

    bool isBackBtnClicked(sf::RenderWindow& window);
};
