#include "Player.h"

Player::Player() {
    name = "Player";
}

Player::Player(const std::string& playerName) {
    name = playerName;
}

void Player::setName(const std::string& playerName) {
    name = playerName;
}

std::string Player::getName() const {
    return name;
}

Board& Player::getBoard() {
    return board;
}
