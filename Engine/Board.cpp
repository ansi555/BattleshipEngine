#include "Board.h"

#include <iostream>

Board::Board(int boardWidth, int boardHeight) {
    width = boardWidth;
    height = boardHeight;
}

int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}

bool Board::placeShip(Ship ship) {
    ships.push_back(ship);
    return true;
}

void Board::markSurroundingCells(const Ship& ship) {
    for (const Coordinate& position : ship.getPositions()) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                Coordinate surroundingCell;

                surroundingCell.x = position.x + dx;
                surroundingCell.y = position.y + dy;

                // Außerhalb des Boards?

                if (surroundingCell.x < 0 || surroundingCell.x >= width || surroundingCell.y < 0 ||
                    surroundingCell.y >= height) {
                    continue;
                }

                // Gehört die Zelle zum Schiff?

                bool isShipCell = false;

                for (const Coordinate& shipPosition : ship.getPositions()) {
                    if (shipPosition.x == surroundingCell.x && shipPosition.y == surroundingCell.y) {
                        isShipCell = true;
                        break;
                    }
                }

                if (isShipCell) {
                    continue;
                }

                // Schon als Miss vorhanden?

                bool alreadyExists = false;

                for (const Coordinate& miss : misses) {
                    if (miss.x == surroundingCell.x && miss.y == surroundingCell.y) {
                        alreadyExists = true;
                        break;
                    }
                }

                if (!alreadyExists) {
                    misses.push_back(surroundingCell);
                }
            }
        }
    }
}

bool Board::shoot(Coordinate coord) {
    for (int i = 0; i < ships.size(); i++) {
        if (ships[i].hit(coord)) {
            hits.push_back(coord);

            if (ships[i].isSunk()) {
                markSurroundingCells(ships[i]);

                std::cout << "Schiff versenkt!" << std::endl;
            }

            return true;
        }
    }
    misses.push_back(coord);
    return false;
}

bool Board::allShipsDestroyed() {
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i].isSunk() == false) {
            return false;
        }
    }

    return true;
}

const std::vector<Ship>& Board::getShips() const {
    return ships;
}
const std::vector<Coordinate>& Board::getHits() const {
    return hits;
}
const std::vector<Coordinate>& Board::getMisses() const {
    return misses;
}
