#include "BoardRenderer.h"

#include "../Assets/Colors.h"

void BoardRenderer::init(sf::Font& font) {
    player1BoardLabel.setFont(font);
    player1BoardLabel.setString("Eigenes Board");
    player1BoardLabel.setCharacterSize(24);
    player1BoardLabel.setFillColor(Colors::Black);

    player2BoardLabel.setFont(font);
    player2BoardLabel.setString("Gegner-Board");
    player2BoardLabel.setCharacterSize(24);
    player2BoardLabel.setFillColor(Colors::Black);
}

void BoardRenderer::render(sf::RenderWindow& window, Board& board, bool leftBoard) {
    int cellSize = 25;

    int boardWidth = board.getWidth() * cellSize;
    int boardHeight = board.getHeight() * cellSize;
    int gap = 100;
    int totalWidth = boardWidth * 2 + gap;

    int startX = (window.getSize().x - totalWidth) / 2;
    int boardX;
    int boardY = 200;

    if (leftBoard) {
        boardX = startX;

        player1BoardLabel.setPosition(boardX + (boardWidth - player1BoardLabel.getGlobalBounds().width) / 2,
                                      boardY - 50);
        window.draw(player1BoardLabel);
    } else {
        boardX = startX + boardWidth + gap;

        player2BoardLabel.setPosition(boardX + (boardWidth - player2BoardLabel.getGlobalBounds().width) / 2,
                                      boardY - 50);
        window.draw(player2BoardLabel);
    }

    sf::RectangleShape border;

    border.setPosition(boardX - 4, boardY - 4);

    border.setSize(sf::Vector2f(boardWidth + 8, boardHeight + 8));

    border.setFillColor(sf::Color::Transparent);

    border.setOutlineColor(Colors::DarkGreen);

    border.setOutlineThickness(3);

    window.draw(border);
    for (int row = 0; row < board.getHeight(); row++) {
        for (int col = 0; col < board.getWidth(); col++) {
            sf::RectangleShape cell;

            cell.setSize(sf::Vector2f(cellSize, cellSize));

            cell.setPosition(boardX + col * cellSize, boardY + row * cellSize);

            cell.setFillColor(Colors::CellGrey);

            cell.setOutlineColor(Colors::GridLine);

            cell.setOutlineThickness(1);

            window.draw(cell);
        }
    }
}
