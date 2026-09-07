#include "GameEngine.h"

GameEngine::GameEngine()

    : player1("Spieler 1"),

      player2("Spieler 2")

{

    player1Turn = true;

    running = true;
}
Player &GameEngine::currentPlayer()
{
    if (player1Turn)
    {
        return player1;
    }
    return player2;
}
Player &GameEngine::enemyPlayer()
{
    if (player1Turn)
    {
        return player2;
    }
    return player1;
}
bool GameEngine::isRunning()
{
    return true;
}
bool GameEngine::fire(int x, int y)
{
    Coordinate coord(x, y);
    bool hit =
        enemyPlayer().getBoard().shoot(coord);

    if (player1Turn)
    {
        player1Turn = false;
    }
    else
    {
        player1Turn = true;
    }
    return hit;
}
bool GameEngine::isGameOver()
{
    if (player1.getBoard().allShipsDestroyed())
    {
        return true;
    }
    if (player2.getBoard().allShipsDestroyed())
    {
        return true;
    }
    return false;
}
