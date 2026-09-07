#include "Board.h"

Board::Board(int boardWidth, int boardHeight)
{
    width = boardWidth;
    height = boardHeight;
}

int Board::getWidth()
{
    return width;
}

int Board::getHeight()
{
    return height;
}

bool Board::placeShip(Ship ship)
{
    ships.push_back(ship);
    return true;
}

bool Board::shoot(Coordinate coord)
{
    for (size_t i = 0; i < ships.size(); i++)
    {
        if (ships[i].hit(coord))
        {
            return true;
        }
    }

    return false;
}

bool Board::allShipsDestroyed()
{
    for (size_t i = 0; i < ships.size(); i++)
    {
        if (ships[i].isSunk() == false)
        {
            return false;
        }
    }

    return true;
}
