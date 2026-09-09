#pragma once

#include <vector>

#include "Coordinate.h"
#include "Ship.h"

class Board {
   private:
    int width;
    int height;

    std::vector<Coordinate> selectedPlacementCells;

    std::vector<Ship> ships;

    std::vector<Coordinate> hits;
    std::vector<Coordinate> misses;

   public:
    Board(int width = 10, int height = 10);

    void togglePlacementCell(Coordinate coord);
    const std::vector<Coordinate>& getSelectedPlacementCells() const;

    int getWidth();
    int getHeight();

    bool placeShip(Ship ship);

    bool shoot(Coordinate coord);

    bool allShipsDestroyed();

    void markSurroundingCells(const Ship& ship);

    const std::vector<Ship>& getShips() const;
    const std::vector<Coordinate>& getHits() const;
    const std::vector<Coordinate>& getMisses() const;
};
