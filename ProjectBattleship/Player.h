#pragma once

#include <string>
#include "Board.h"

class Player
{
private:
	std::string name;
	Board board;

public:
	Player(const std::string& name);

	Board& getBoard();

	const std::string& getName() const;
};