#pragma once

#include <string>
#include <vector>

#include "Coordinate.h"
#include "Ship.h"

class Board {
   private:
    int width;
    int height;

    std::vector<Ship> ships;

    std::vector<Coordinate> hits;
    std::vector<Coordinate> misses;
    std::vector<Coordinate> selectedPlacementCells;

    bool shipsVisible = false;

    bool consoleVisible = false;

   public:
    Board(int width = 15, int height = 15);

    int getWidth();
    int getHeight();

    bool placeShip(Ship ship);

    bool shoot(Coordinate coord);

    bool allShipsDestroyed();

    void markSurroundingCells(const Ship& ship);

    int countPlacedShipsByLength(int length) const;

    bool isStraightShip(const std::vector<Coordinate>& ship) const;

    bool isPlacementReady() const;

    std::vector<std::vector<Coordinate>> getPlacementShips() const;

    void togglePlacementCell(Coordinate coord);

    bool shipsAreSeparated(const std::vector<std::vector<Coordinate>>& ships) const;

    std::vector<Coordinate> getInvalidPlacementCells() const;

    void toggleShipVisibility();
    bool areShipsVisible() const;

    void finishPlacement();

    void loadPlacementFromJson(const std::string& filePath);

    void generateRandomPlacement();

    const std::vector<Coordinate>& getSelectedPlacementCells() const;
    const std::vector<Ship>& getShips() const;
    const std::vector<Coordinate>& getHits() const;
    const std::vector<Coordinate>& getMisses() const;
};
