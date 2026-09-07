#pragma once
#include "Player.h"

class GameEngine
{
private:
    Player player1;
    Player player2;
    bool player1Turn;

public:
    bool running;

    GameEngine();
    bool isRunning();
    bool fire(int x, int y);
    bool isGameOver();
    Player &currentPlayer();
    Player &enemyPlayer();
};
