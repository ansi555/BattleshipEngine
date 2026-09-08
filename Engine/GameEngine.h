#pragma once
#include <vector>

#include "Move.h"
#include "Player.h"

class GameEngine {
   private:
    Player player1;
    Player player2;
    bool player1Turn;

    std::vector<Move> moveHistory;

   public:
    bool running;

    GameEngine();
    bool isRunning();
    bool fire(int x, int y);
    bool isGameOver();
    Player& currentPlayer();
    Player& enemyPlayer();

    void addMove(Move move);

    const std::vector<Move>& getMoveHistory();
};
