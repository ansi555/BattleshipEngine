#include "CommandParser.h"

#include <cctype>

bool CommandParser::isCoordinate(const std::string& input) {
    if (input.length() != 3) {
        return false;
    }
    char column = std::toupper(input[0]);
    return column >= 'A' && column <= 'J' && std::isdigit(input[1]) && std::isdigit(input[2]);
}

Coordinate CommandParser::parseCoordinate(const std::string& input) {
    char column = std::toupper(input[0]);
    int x = column - 'A';
    int y = std::stoi(input.substr(1)) - 1;
    return Coordinate(x, y);
}
