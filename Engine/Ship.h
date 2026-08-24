#include <vector>
#include "Coordinate.h"

class Ship {
    private:
        std::vector<Coordinate> positions;
        std::vector<bool> shipHits;

    public:
        Ship(const std::vector<Coordinate> &coords);

        bool hit(const Coordinate &coord);
        bool isSunk();
};
