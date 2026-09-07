#include "BoardRenderer.h"

#include "Assets/Colors.h"

void BoardRenderer::render(
    sf::RenderWindow &window,
    Board &board)
{
    int cellSize = 40;

    int startX = 100;
    int startY = 0;

    for (int row = 0; row < board.getHeight(); row++)
    {
        for (int col = 0; col < board.getWidth(); col++)
        {
            sf::RectangleShape cell;

            cell.setSize(
                sf::Vector2f(cellSize, cellSize));

            cell.setPosition(
                startX + col * cellSize,
                startY + row * cellSize);

            cell.setFillColor(
                Colors::DarkGreen);

            cell.setOutlineColor(
                Colors::Black);

            cell.setOutlineThickness(1);

            window.draw(cell);
        }
    }
}
