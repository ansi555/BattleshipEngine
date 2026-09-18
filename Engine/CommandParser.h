#pragma once

#include <string>

#include "Coordinate.h"

class CommandParser {
   public:
    static bool isCoordinate(const std::string& input);
    static Coordinate parseCoordinate(const std::string& input);
};
