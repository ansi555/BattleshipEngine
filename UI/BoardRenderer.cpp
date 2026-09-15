#include "BoardRenderer.h"

#include "../Assets/Colors.h"

void BoardRenderer::init(sf::Font& font) {
    //  ------------------------------
    //  Setting up Labels
    //  -----------------------------

    player1BoardLabel.setFont(font);
    player1BoardLabel.setCharacterSize(18);
    player1BoardLabel.setFillColor(Colors::Black);

    player2BoardLabel.setFont(font);
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

    border.setFillColor(sf::Color::Transparent);

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

    readyBtn.setSize(sf::Vector2f(100, 40));
    readyBtn.setFillColor(Colors::SuccessGreen);
    readyBtn.setOutlineColor(Colors::DarkGreen);
    readyBtn.setOutlineThickness(2);

    readyBtnLabel.setFont(font);
    readyBtnLabel.setString("Fertig!");
    readyBtnLabel.setCharacterSize(18);
    readyBtnLabel.setFillColor(Colors::Black);

    visibilityBtn.setSize(sf::Vector2f(100, 30));
    visibilityBtn.setOutlineColor(Colors::DarkGreen);
    visibilityBtn.setOutlineThickness(2);
    visibilityBtn.setPosition(150, 50);

    visibilityBtnLabel.setFont(font);
    visibilityBtnLabel.setString("Sichtbarkeit");
    visibilityBtnLabel.setCharacterSize(15);
    visibilityBtnLabel.setFillColor(Colors::Black);
    visibilityBtnLabel.setPosition(162, 55);

    jsonBtn.setSize(sf::Vector2f(150, 40));
    jsonBtn.setPosition(150, 50);
    jsonBtn.setFillColor(Colors::SuccessGreen);
    jsonBtn.setOutlineColor(Colors::DarkGreen);
    jsonBtn.setOutlineThickness(2);

    jsonBtnLabel.setFont(font);
    jsonBtnLabel.setString("JSON-Data");
    jsonBtnLabel.setCharacterSize(18);
    jsonBtnLabel.setFillColor(Colors::Black);
    jsonBtnLabel.setPosition(170, 58);

    gameOverLabel.setFont(font);
    gameOverLabel.setCharacterSize(36);
    gameOverLabel.setFillColor(Colors::ErrorRed);

    winnerLabel.setFont(font);
    winnerLabel.setCharacterSize(24);
    winnerLabel.setFillColor(Colors::SuccessGreen);
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

void BoardRenderer::render(sf::RenderWindow& window, Board& board, const std::string& playerName, bool leftBoard,
                           bool showPlacementInfo, bool active) {
    //  ------------------------------
    //  Positioning Labels
    //  ------------------------------
    BoardArea area = getBoardArea(window, board, leftBoard);

    window.draw(backBtn);
    window.draw(backBtnLabel);

    const int cellSize = 35;

    if (leftBoard) {
        player1BoardLabel.setString(playerName);
        player1BoardLabel.setPosition(area.x + (area.width - player1BoardLabel.getGlobalBounds().width) / 2,
                                      area.y - 95);
        window.draw(player1BoardLabel);
    } else {
        player2BoardLabel.setString(playerName);
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

    border.setPosition(area.x - 4, area.y - 4);
    border.setSize(sf::Vector2f(area.width + 8, area.height + 8));
    if (active) {
        border.setOutlineColor(Colors::SuccessGreen);
        border.setOutlineThickness(6);
    } else {
        border.setOutlineColor(Colors::DarkGreen);
        border.setOutlineThickness(3);
    }

    window.draw(border);

    std::string fleetInfo = "4er: " + std::to_string(board.countPlacedShipsByLength(4)) +
                            " / 1\n"
                            "3er: " +
                            std::to_string(board.countPlacedShipsByLength(3)) +
                            " / 2\n"
                            "2er: " +
                            std::to_string(board.countPlacedShipsByLength(2)) + " / 3\n";

    float centerX = area.x + area.width / 2.0f;

    readyBtn.setPosition(centerX - 50, area.y + area.height + 170);

    readyBtnLabel.setPosition(centerX - readyBtnLabel.getGlobalBounds().width / 2.f, area.y + area.height + 178);

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

    if (board.areShipsVisible()) {
        visibilityBtn.setFillColor(Colors::SuccessGreen);
    } else {
        visibilityBtn.setFillColor(Colors::ErrorRed);
    }

    if (showPlacementInfo) {
        window.draw(fleetInfoLabel);
        window.draw(readyLabel);
        window.draw(readyBtn);
        window.draw(readyBtnLabel);

        window.draw(jsonBtn);
        window.draw(jsonBtnLabel);
    } else if (active) {
        window.draw(visibilityBtn);
        window.draw(visibilityBtnLabel);
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

void BoardRenderer::renderGameOver(sf::RenderWindow& window, const std::string& winner) {
    gameOverLabel.setString("GAME OVER");

    winnerLabel.setString(winner + " gewinnt!");

    gameOverLabel.setPosition(window.getSize().x / 2.f - gameOverLabel.getGlobalBounds().width / 2.f, 700);

    winnerLabel.setPosition(window.getSize().x / 2.f - winnerLabel.getGlobalBounds().width / 2.f, 750);

    window.draw(gameOverLabel);
    window.draw(winnerLabel);
}

bool BoardRenderer::isBackBtnClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return backBtn.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool BoardRenderer::isReadyBtnClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return readyBtn.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool BoardRenderer::isVisibilityBtnClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return visibilityBtn.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool BoardRenderer::isJsonBtnClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return jsonBtn.getGlobalBounds().contains(mousePos.x, mousePos.y);
}
