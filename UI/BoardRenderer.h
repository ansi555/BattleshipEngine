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

    sf::RectangleShape border;

    sf::Text fleetInfoLabel;
    sf::Text readyLabel;

    sf::RectangleShape backBtn;
    sf::Text backBtnLabel;

    sf::RectangleShape readyBtn;
    sf::Text readyBtnLabel;

    sf::RectangleShape visibilityBtn;
    sf::Text visibilityBtnLabel;

    sf::RectangleShape jsonBtn;
    sf::Text jsonBtnLabel;

    sf::Text gameOverLabel;
    sf::Text winnerLabel;

   public:
    void init(sf::Font& font);

    Coordinate getClickedCell(sf::RenderWindow& window, Board& board, bool leftBoard);

    void render(sf::RenderWindow& window, Board& board, bool leftBoard, bool showPlacementInfo, bool active);

    BoardArea getBoardArea(sf::RenderWindow& window, Board& board, bool leftBoard);

    bool isBackBtnClicked(sf::RenderWindow& window);

    bool isReadyBtnClicked(sf::RenderWindow& window);

    bool isVisibilityBtnClicked(sf::RenderWindow& window);

    bool isJsonBtnClicked(sf::RenderWindow& window);

    void renderGameOver(sf::RenderWindow& window, const std::string& winner);
};
