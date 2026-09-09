#pragma once

#include <vector>

#include "Coordinate.h"

class Ship {
   private:
    std::vector<Coordinate> positions;
    std::vector<bool> shipHits;

   public:
    Ship(std::vector<Coordinate> coords);

    bool hit(Coordinate coord);
    bool isSunk() const;

    const std::vector<Coordinate>& getPositions() const;
};
