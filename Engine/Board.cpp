#include "Board.h"

#include <fstream>
#include <iostream>
#include <regex>

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

int Board::countPlacedShipsByLength(int length) const {
    int count = 0;

    auto ships = getPlacementShips();

    for (const auto& ship : ships) {
        if (ship.size() == length && isStraightShip(ship)) {
            count++;
        }
    }

    return count;
}

bool Board::shipsAreSeparated(const std::vector<std::vector<Coordinate>>& ships) const {
    for (int i = 0; i < ships.size(); i++) {
        for (int j = i + 1; j < ships.size(); j++) {
            for (const Coordinate& cell1 : ships[i]) {
                for (const Coordinate& cell2 : ships[j]) {
                    int dx = std::abs(cell1.x - cell2.x);

                    int dy = std::abs(cell1.y - cell2.y);

                    if (dx <= 1 && dy <= 1) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool Board::isStraightShip(const std::vector<Coordinate>& ship) const {
    if (ship.size() < 2) {
        return false;
    }

    bool sameX = true;
    bool sameY = true;

    for (size_t i = 1; i < ship.size(); i++) {
        if (ship[i].x != ship[0].x) {
            sameX = false;
        }

        if (ship[i].y != ship[0].y) {
            sameY = false;
        }
    }

    if (!sameX && !sameY) {
        return false;
    }

    if (sameX) {
        int minY = ship[0].y;
        int maxY = ship[0].y;

        for (const Coordinate& cell : ship) {
            minY = std::min(minY, cell.y);
            maxY = std::max(maxY, cell.y);
        }

        return (maxY - minY + 1) == static_cast<int>(ship.size());
    }

    int minX = ship[0].x;
    int maxX = ship[0].x;

    for (const Coordinate& cell : ship) {
        minX = std::min(minX, cell.x);
        maxX = std::max(maxX, cell.x);
    }

    return (maxX - minX + 1) == static_cast<int>(ship.size());
}

bool Board::isPlacementReady() const {
    auto ships = getPlacementShips();

    /* std::cout << "\n===== Erkannte Schiffe =====\n";
    for (int i = 0; i < ships.size(); i++) {
        std::cout << "Schiff " << i + 1 << ": " << ships[i].size() << " Felder" << std::endl;

        for (const Coordinate& cell : ships[i]) {
            std::cout << "  " << cell.toString() << std::endl;
        }
    } */

    if (selectedPlacementCells.size() != 16) {
        return false;
    }

    for (const auto& ship : ships) {
        std::cout << "Straight: " << isStraightShip(ship) << std::endl;
    }

    if (!shipsAreSeparated(ships)) {
        return false;
    }

    return countPlacedShipsByLength(4) == 1 && countPlacedShipsByLength(3) == 2 && countPlacedShipsByLength(2) == 3;
}

std::vector<std::vector<Coordinate>> Board::getPlacementShips() const {
    std::vector<std::vector<Coordinate>> ships;

    std::vector<bool> visited(selectedPlacementCells.size(), false);

    for (size_t i = 0; i < selectedPlacementCells.size(); i++) {
        if (visited[i]) {
            continue;
        }

        std::vector<Coordinate> currentShip;
        std::vector<size_t> stack;

        stack.push_back(i);
        visited[i] = true;

        while (!stack.empty()) {
            size_t currentIndex = stack.back();

            stack.pop_back();

            currentShip.push_back(selectedPlacementCells[currentIndex]);

            for (size_t j = 0; j < selectedPlacementCells.size(); j++) {
                if (visited[j]) {
                    continue;
                }

                int dx = std::abs(selectedPlacementCells[currentIndex].x - selectedPlacementCells[j].x);

                int dy = std::abs(selectedPlacementCells[currentIndex].y - selectedPlacementCells[j].y);

                bool neighbour = (dx == 1 && dy == 0) || (dx == 0 && dy == 1);

                if (neighbour) {
                    visited[j] = true;
                    stack.push_back(j);
                }
            }
        }

        ships.push_back(currentShip);
    }

    return ships;
}

void Board::togglePlacementCell(Coordinate coord) {
    for (size_t i = 0; i < selectedPlacementCells.size(); i++) {
        if (selectedPlacementCells[i].x == coord.x && selectedPlacementCells[i].y == coord.y) {
            selectedPlacementCells.erase(selectedPlacementCells.begin() + i);

            return;
        }
    }

    selectedPlacementCells.push_back(coord);
}

std::vector<Coordinate> Board::getInvalidPlacementCells() const {
    std::vector<Coordinate> invalidCells;

    auto ships = getPlacementShips();

    for (const auto& ship : ships) {
        if (!isStraightShip(ship)) {
            invalidCells.insert(invalidCells.end(), ship.begin(), ship.end());
        }
    }

    for (size_t i = 0; i < ships.size(); i++) {
        for (size_t j = i + 1; j < ships.size(); j++) {
            bool touching = false;

            for (const Coordinate& cell1 : ships[i]) {
                for (const Coordinate& cell2 : ships[j]) {
                    int dx = std::abs(cell1.x - cell2.x);

                    int dy = std::abs(cell1.y - cell2.y);

                    if (dx <= 1 && dy <= 1) {
                        touching = true;
                        break;
                    }
                }

                if (touching) {
                    break;
                }
            }

            if (touching) {
                invalidCells.insert(invalidCells.end(), ships[i].begin(), ships[i].end());

                invalidCells.insert(invalidCells.end(), ships[j].begin(), ships[j].end());
            }
        }
    }

    return invalidCells;
}

void Board::toggleShipVisibility() {
    shipsVisible = !shipsVisible;
}

bool Board::areShipsVisible() const {
    return shipsVisible;
}

void Board::finishPlacement() {
    auto placementShips = getPlacementShips();
    for (const auto& shipCells : placementShips) {
        Ship ship(shipCells);
        placeShip(ship);
    }
}

void Board::loadPlacementFromJson(const std::string& filePath) {
    selectedPlacementCells.clear();
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Could not open " << filePath << std::endl;
        return;
    }
    std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::regex coordinatePattern(R"(\[(\d+),(\d+)])");
    std::sregex_iterator begin(json.begin(), json.end(), coordinatePattern);
    std::sregex_iterator end;
    for (auto it = begin; it != end; ++it) {
        int x = std::stoi((*it)[1]);
        int y = std::stoi((*it)[2]);
        selectedPlacementCells.push_back(Coordinate(x, y));
    }
    std::cout << "Loaded " << selectedPlacementCells.size() << " placement cells." << std::endl;
}

const std::vector<Coordinate>& Board::getSelectedPlacementCells() const {
    return selectedPlacementCells;
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
