#pragma once

struct Coordinate
{
    int x;
    int y;

    Coordinate(int xVal = 0, int yVal = 0)
    {
        x = xVal;
        y = yVal;
    }

    bool equals(const Coordinate other)
    {
        if (x == other.x && y == other.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
