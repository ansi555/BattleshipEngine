#include "Ship.h"

Ship::Ship(const std::vector<Coordinate> &coords) {
    positions = coords;

    for (int i = 0; i < coords.size(); i++) {
        shipHits.push_back(false);
    }
}

bool Ship::hit(const Coordinate &coord) {
    for (int i = 0; i < positions.size(); i++) {
        if (positions[i].equals(coord)) {
            shipHits[i] = true;
            return true;
        }
    }

    return false;
}

bool Ship::isSunk() {
    for (int i = 0; i < shipHits.size(); i++) {
        if (shipHits[i] == false) {
            return false;
        }
    }

    return true;
}
