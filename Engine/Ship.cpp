#include "Ship.h"

Ship::Ship(const std::vector<Coordinate> coords) {
    positions = coords;

    for (int i = 0; i < coords.size(); i++) {
        shipHits.push_back(false);
    }
}

bool Ship::hit(const Coordinate coord) {
    for (int i = 0; i < positions.size(); i++) {
        if (positions[i].equals(coord)) {
            shipHits[i] = true;
            return true;
        }
    }

    return false;
}

bool Ship::isSunk() {
    for (bool hit : shipHits) {
        if (!hit) {
            return false;
        }
    }

    return true;
}

const std::vector<Coordinate>& Ship::getPositions() const {
    return positions;
}
