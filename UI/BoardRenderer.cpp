#include "BoardRenderer.h"

#include "../Assets/Colors.h"

void BoardRenderer::init(sf::Font& font) {
    //  ------------------------------
    //  Setting up Labels
    //  -----------------------------

    player1BoardLabel.setFont(font);
    player1BoardLabel.setString("Player 1");
    player1BoardLabel.setCharacterSize(18);
    player1BoardLabel.setFillColor(Colors::Black);

    player2BoardLabel.setFont(font);
    player2BoardLabel.setString("Player 2");
    player2BoardLabel.setCharacterSize(18);
    player2BoardLabel.setFillColor(Colors::Black);

    //  ------------------------------
    //  Setting up Labels for coordinates
    //  ------------------------------

    for (int i = 0; i < 10; i++) {
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

    fleetInfoLabel.setFont(font);
    fleetInfoLabel.setCharacterSize(20);

    readyLabel.setFont(font);
    readyLabel.setCharacterSize(24);

    backBtn.setSize(sf::Vector2f(43, 30));
    backBtn.setPosition(50, 50);
    backBtn.setFillColor(Colors::SuccessGreen);
    backBtn.setOutlineColor(Colors::DarkGreen);
    backBtn.setOutlineThickness(1);

    backBtnLabel.setFont(font);
    backBtnLabel.setString("Back");
    backBtnLabel.setCharacterSize(15);
    backBtnLabel.setFillColor(Colors::Black);
    backBtnLabel.setPosition(55, 55);
}

BoardArea BoardRenderer::getBoardArea(sf::RenderWindow& window, Board& board, bool leftBoard) {
    const int cellSize = 35;
    const int gap = 200;
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

void BoardRenderer::render(sf::RenderWindow& window, Board& board, bool leftBoard, bool showPlacementInfo) {
    //  ------------------------------
    //  Positioning Labels
    //  ------------------------------
    BoardArea area = getBoardArea(window, board, leftBoard);

    window.draw(backBtn);
    window.draw(backBtnLabel);

    const int cellSize = 35;

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

    for (int col = 0; col < board.getWidth(); col++) {
        columnLabels[col].setPosition(
            area.x + col * cellSize + (cellSize - columnLabels[col].getGlobalBounds().width) / 2, area.y - 40);

        window.draw(columnLabels[col]);
    }

    for (int row = 0; row < board.getHeight(); row++) {
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

    std::string fleetInfo = "4er: " + std::to_string(board.countPlacedShipsByLength(4)) +
                            " / 1\n"
                            "3er: " +
                            std::to_string(board.countPlacedShipsByLength(3)) +
                            " / 2\n"
                            "2er: " +
                            std::to_string(board.countPlacedShipsByLength(2)) + " / 3\n";

    float centerX = area.x + area.width / 2.0f;

    fleetInfoLabel.setString(fleetInfo);
    fleetInfoLabel.setFillColor(Colors::Black);
    fleetInfoLabel.setPosition(centerX - fleetInfoLabel.getGlobalBounds().width / 2.0f, area.y + area.height + 30);

    if (board.isPlacementReady()) {
        readyLabel.setString("READY");
        readyLabel.setFillColor(Colors::SuccessGreen);
    } else {
        readyLabel.setString("NOT READY");
        readyLabel.setFillColor(Colors::ErrorRed);
    }
    readyLabel.setPosition(centerX - readyLabel.getGlobalBounds().width / 2.0f, area.y + area.height + 120);

    if (showPlacementInfo) {
        window.draw(fleetInfoLabel);
        window.draw(readyLabel);
    }

    //  ------------------------------
    //  Positioning and generated cells
    //  ------------------------------
}

Coordinate BoardRenderer::getClickedCell(sf::RenderWindow& window, Board& board, bool leftBoard) {
    const int cellSize = 35;
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

bool BoardRenderer::isBackBtnClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    return backBtn.getGlobalBounds().contains(mousePos.x, mousePos.y);
}
