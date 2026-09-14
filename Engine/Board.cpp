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

const std::vector<Coordinate>& Board::getSelectedPlacementCells() const {
    return selectedPlacementCells;
}

void Board::togglePlacementCell(Coordinate coord) {
    for (int i = 0; i < selectedPlacementCells.size(); i++) {
        if (selectedPlacementCells[i].x == coord.x && selectedPlacementCells[i].y == coord.y) {
            // std::cout << "Removed: " << coord.toString() << std::endl;
            selectedPlacementCells.erase(selectedPlacementCells.begin() + i);
            return;
        }
    }
    // std::cout << "Added: " << coord.toString() << std::endl;

    selectedPlacementCells.push_back(coord);
}

bool areNeighbours(const Coordinate& a, const Coordinate& b) {
    int dx = std::abs(a.x - b.x);
    int dy = std::abs(a.y - b.y);

    return dx <= 1 && dy <= 1;
}

void collectShip(const Coordinate& cell, const std::vector<Coordinate>& cells, std::vector<Coordinate>& ship,
                 std::vector<bool>& visited, int index) {
    visited[index] = true;
    ship.push_back(cells[index]);
    for (int i = 0; i < cells.size(); i++) {
        if (visited[i]) {
            continue;
        }
        int dx = std::abs(cells[index].x - cells[i].x);
        int dy = std::abs(cells[index].y - cells[i].y);
        bool connected = (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
        if (connected) {
            collectShip(cells[i], cells, ship, visited, i);
        }
    }
}

bool Board::isPlacementReady() const {
    if (selectedPlacementCells.size() != 16) {
        return false;
    }
    for (int i = 0; i < selectedPlacementCells.size(); i++) {
        for (int j = i + 1; j < selectedPlacementCells.size(); j++) {
            int dx = std::abs(selectedPlacementCells[i].x - selectedPlacementCells[j].x);
            int dy = std::abs(selectedPlacementCells[i].y - selectedPlacementCells[j].y);
            bool orthogonal = (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
            bool diagonal = (dx == 1 && dy == 1);
            if (diagonal) {
                return false;
            }
        }
    }
    std::vector<bool> visited(selectedPlacementCells.size(), false);
    int count4 = 0;
    int count3 = 0;
    int count2 = 0;
    for (int i = 0; i < selectedPlacementCells.size(); i++) {
        if (visited[i]) {
            continue;
        }
        std::vector<Coordinate> ship;
        collectShip(selectedPlacementCells[i], selectedPlacementCells, ship, visited, i);
        int length = ship.size();
        if (length == 4) {
            count4++;
        } else if (length == 3) {
            count3++;
        } else if (length == 2) {
            count2++;
        } else {
            return false;
        }
    }
    return count4 == 1 && count3 == 2 && count2 == 3;
}

int Board::countPlacedShipsByLength(int length) const {
    std::vector<bool> visited(selectedPlacementCells.size(), false);

    int count = 0;

    for (int i = 0; i < selectedPlacementCells.size(); i++) {
        if (visited[i]) {
            continue;
        }

        std::vector<Coordinate> ship;

        collectShip(selectedPlacementCells[i], selectedPlacementCells, ship, visited, i);

        if (ship.size() == length) {
            count++;
        }
    }

    return count;
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
