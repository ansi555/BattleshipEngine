#pragma once

#include "Board.h"
#include <string>

class Player
{
private:
	std::string name;
	Board board;

public:
	Player(std::string name);

	Board &getBoard();

	std::string getName();
};
