#include "ShipRenderer.h"

#include "../Assets/Colors.h"

void ShipRenderer::render(sf::RenderWindow& window, Board& board, BoardArea area, bool leftBoard) {
    const int cellSize = 25;

    for (int row = 0; row < board.getHeight(); row++) {
        for (int col = 0; col < board.getWidth(); col++) {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(area.x + col * cellSize, area.y + row * cellSize);
            cell.setFillColor(Colors::CellGrey);
            cell.setOutlineColor(Colors::OnyxHeart);
            cell.setOutlineThickness(1);

            bool containsShip = false;

            for (const Ship& ship : board.getShips()) {
                for (const Coordinate& position : ship.getPositions()) {
                    if (position.x == col && position.y == row) {
                        containsShip = true;
                        break;
                    }
                }
                if (containsShip) {
                    break;
                }
            }

            if (containsShip) {
                cell.setFillColor(Colors::Purpur);
            } else {
                cell.setFillColor(Colors::CellGrey);
            }

            bool isHit = false;

            for (const Coordinate& hit : board.getHits()) {
                if (hit.x == col && hit.y == row) {
                    isHit = true;
                    break;
                }
            }

            if (isHit) {
                cell.setFillColor(Colors::SuccessGreen);
            } else if (containsShip && leftBoard) {
                cell.setFillColor(Colors::ErrorRed);
            } else {
                cell.setFillColor(Colors::CellGrey);
            }

            bool isMiss = false;

            for (const Coordinate& miss : board.getMisses()) {
                if (miss.x == col && miss.y == row) {
                    isMiss = true;
                    break;
                }
            }

            if (isHit) {
                cell.setFillColor(Colors::SuccessGreen);
            } else if (isMiss) {
                cell.setFillColor(Colors::WaterBlue);
            } else if (containsShip && leftBoard) {
                cell.setFillColor(Colors::SuccessGreen);
            } else {
                cell.setFillColor(Colors::CellGrey);
            }

            window.draw(cell);
        }
    }
}
