#pragma once

#include "Ship.h"
#include <vector>

class Board
{
private:
    int width;
    int height;

    std::vector<Ship> ships;
    std::vector<Coordinate> shots;

public:
    Board(int width = 10, int height = 10);

    bool placeShip(const Ship ship);

    bool shoot(const Coordinate coord);

    bool allShipsDestroyed();
};
