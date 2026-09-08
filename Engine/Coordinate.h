#pragma once

#include <string>

struct Coordinate {
    int x;
    int y;

    Coordinate(int xVal = 0, int yVal = 0) {
        x = xVal;
        y = yVal;
    }

    bool equals(const Coordinate other) {
        if (x == other.x && y == other.y) {
            return true;
        } else {
            return false;
        }
    }

    std::string toString() const {
        char column = 'A' + x;

        std::string row = std::to_string(y + 1);

        if (y < 9) {
            row = "0" + row;
        }

        return std::string(1, column) + row;
    }
};
