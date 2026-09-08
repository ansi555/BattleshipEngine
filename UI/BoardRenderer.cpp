#include "BoardRenderer.h"

#include "../Assets/Colors.h"

void BoardRenderer::init(sf::Font& font) {
    //  ------------------------------
    //  Setting up Labels
    //  -----------------------------

    player1BoardLabel.setFont(font);
    player1BoardLabel.setString("Eigenes Board");
    player1BoardLabel.setCharacterSize(24);
    player1BoardLabel.setFillColor(Colors::Black);

    player2BoardLabel.setFont(font);
    player2BoardLabel.setString("Gegner-Board");
    player2BoardLabel.setCharacterSize(24);
    player2BoardLabel.setFillColor(Colors::Black);

    //  ------------------------------
    //  Setting up Labels for coordinates
    //  ------------------------------

    for (int i = 0; i < 15; i++) {
        columnLabels[i].setFont(font);
        columnLabels[i].setString(std::string(1, 'A' + i));
        columnLabels[i].setCharacterSize(10);
        columnLabels[i].setFillColor(Colors::DarkGreen);

        rowLabels[i].setFont(font);
        std::string number = std::to_string(i + 1);
        if (i < 9) {
            number = "0" + number;
        }
        rowLabels[i].setString(number);
        rowLabels[i].setCharacterSize(10);
        rowLabels[i].setFillColor(Colors::DarkGreen);
    }
}

BoardArea BoardRenderer::getBoardArea(sf::RenderWindow& window, Board& board, bool leftBoard) {
    const int cellSize = 25;
    const int gap = 100;
    const int boardY = 200;

    int boardWidth = board.getWidth() * cellSize;
    int boardHeight = board.getHeight() * cellSize;
    int totalWidth = boardWidth * 2 + gap;
    int startX = (window.getSize().x - totalWidth) / 2;

    BoardArea area;

    area.width = boardWidth;
    area.height = boardHeight;
    area.y = boardY;

    if (leftBoard) {
        area.x = startX;
    } else {
        area.x = startX + boardWidth + gap;
    }

    return area;
}

void BoardRenderer::render(sf::RenderWindow& window, Board& board, bool leftBoard) {
    //  ------------------------------
    //  Positioning Labels
    //  ------------------------------
    BoardArea area = getBoardArea(window, board, leftBoard);

    const int cellSize = 25;

    if (leftBoard) {
        player1BoardLabel.setPosition(area.x + (area.width - player1BoardLabel.getGlobalBounds().width) / 2,
                                      area.y - 95);
        window.draw(player1BoardLabel);
    } else {
        player2BoardLabel.setPosition(area.x + (area.width - player2BoardLabel.getGlobalBounds().width) / 2,
                                      area.y - 95);
        window.draw(player2BoardLabel);
    }

    //  ------------------------------
    //  Positioning labels for coordinates
    //  ------------------------------

    for (int col = 0; col < 15; col++) {
        columnLabels[col].setPosition(
            area.x + col * cellSize + (cellSize - columnLabels[col].getGlobalBounds().width) / 2, area.y - 40);

        window.draw(columnLabels[col]);
    }

    for (int row = 0; row < 15; row++) {
        if (leftBoard) {
            rowLabels[row].setPosition(
                area.x - rowLabels[row].getGlobalBounds().width - 30,
                area.y + row * cellSize + (cellSize - rowLabels[row].getGlobalBounds().height) / 2);
        } else {
            rowLabels[row].setPosition(area.x + area.width + 30, area.y + row * cellSize + 2);
        }

        window.draw(rowLabels[row]);
    }

    //  ------------------------------
    //  Setting up border
    //  ------------------------------

    sf::RectangleShape border;

    border.setPosition(area.x - 4, area.y - 4);

    border.setSize(sf::Vector2f(area.width + 8, area.height + 8));

    border.setFillColor(sf::Color::Transparent);

    border.setOutlineColor(Colors::DarkGreen);

    border.setOutlineThickness(3);

    window.draw(border);

    //  ------------------------------
    //  Positioning and generated cells
    //  ------------------------------

    for (int row = 0; row < board.getHeight(); row++) {
        for (int col = 0; col < board.getWidth(); col++) {
            sf::RectangleShape cell;

            cell.setSize(sf::Vector2f(cellSize, cellSize));

            cell.setPosition(area.x + col * cellSize, area.y + row * cellSize);

            cell.setFillColor(Colors::CellGrey);

            cell.setOutlineColor(Colors::GridLine);

            cell.setOutlineThickness(1);

            window.draw(cell);
        }
    }
}

Coordinate BoardRenderer::getClickedCell(sf::RenderWindow& window, Board& board, bool leftBoard) {
    const int cellSize = 25;
    BoardArea area = getBoardArea(window, board, leftBoard);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (mousePos.x < area.x || mousePos.x >= area.x + area.width || mousePos.y < area.y ||
        mousePos.y >= area.y + area.height) {
        return Coordinate(-1, -1);
    }
    int col = (mousePos.x - area.x) / cellSize;
    int row = (mousePos.y - area.y) / cellSize;
    return Coordinate(col, row);
}
