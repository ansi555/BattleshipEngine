#include "Player.h"

Player::Player(std::string& name)
	: name(name)
{
}

Board& Player::getBoard()
{
	return board;
}

const std::string& Player::getName() const
{
	return name;
}