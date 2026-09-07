#include "Player.h"

Player::Player(std::string name)
	: name(name)
{
}

Board &Player::getBoard()
{
	return board;
}

std::string Player::getName()
{
	return name;
}
