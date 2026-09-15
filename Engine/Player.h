#pragma once

#include <string>

#include "Board.h"

class Player {
   private:
    std::string name;
    Board board;

   public:
    Player();
    Player(const std::string& playerName);

    void setName(const std::string& playerName);

    std::string getName() const;

    Board& getBoard();
};
