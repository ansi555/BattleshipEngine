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
