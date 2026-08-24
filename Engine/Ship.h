#pragma once

#include "Coordinate.h"
#include <vector>

class Ship
{
private:
    std::vector<Coordinate> positions;
    std::vector<bool> shipHits;

public:
    Ship(std::vector<Coordinate> coords);

    bool hit(Coordinate coord);
    bool isSunk();
};
