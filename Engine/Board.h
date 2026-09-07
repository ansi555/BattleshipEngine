#pragma once

#include "Ship.h"
#include <vector>

class Board
{
private:
    int width;
    int height;

    std::vector<Ship> ships;

public:
    Board(int width = 15, int height = 15);

    int getWidth();
    int getHeight();

    bool placeShip(Ship ship);

    bool shoot(Coordinate coord);

    bool allShipsDestroyed();
};
