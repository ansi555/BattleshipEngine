#include "Window.h"

#include <iostream>

void Window::initGame() {
    player1Board = Board(10, 10);
    player2Board = Board(10, 10);
}

Window::Window() {
    window.create(sf::VideoMode(1600, 900), "BattleshipGame");

    state = MENU;
    font.loadFromFile("Assets/Roboto-Regular.ttf");

    darkModeButton.setSize(sf::Vector2f(150, 40));
    darkModeButton.setFillColor(Colors::SuccessGreen());
    darkModeButtonLabel.setFont(font);
    darkModeButtonLabel.setCharacterSize(16);

    menuRenderer.init(font);
    boardRenderer.init(font);
    // shipRenderer.init(font);

    player1.setName("Finja");
    player2.setName("Ansgar");

    initGame();
}

void Window::resetGame() {
    engine = GameEngine();

    initGame();
}

void Window::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Window::handleEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (isDarkModeButtonClicked()) {
                Colors::toggleDarkMode();
                return;
            }

            if (state == MENU) {
                if (menuRenderer.isTestBoardClicked(window)) {
                    initGame();
                    state = PLACE_SHIPS_P1;
                    return;
                }
            } else if (state == PLACE_SHIPS_P1) {
                Coordinate clickedCell = boardRenderer.getClickedCell(window, player1Board, true);
                if (clickedCell.x != -1) {
                    // std::cout << "Toggle: " << clickedCell.toString() << std::endl;
                    player1Board.togglePlacementCell(clickedCell);
                }
                if (boardRenderer.isBackBtnClicked(window)) {
                    resetGame();
                    state = MENU;
                }
                if (boardRenderer.isReadyBtnClicked(window) && player1Board.isPlacementReady()) {
                    player1Board.finishPlacement();
                    state = PLACE_SHIPS_P2;
                }
                if (boardRenderer.isJsonBtnClicked(window)) {
                    player1Board.generateRandomPlacement();
                    std::cout << "Loaded " << player1Board.getSelectedPlacementCells().size() << " placement cells for "
                              << player1.getName() << "." << std::endl;
                }
            } else if (state == PLACE_SHIPS_P2) {
                Coordinate clickedCell = boardRenderer.getClickedCell(window, player2Board, false);
                if (clickedCell.x != -1) {
                    player2Board.togglePlacementCell(clickedCell);
                }
                if (boardRenderer.isBackBtnClicked(window)) {
                    resetGame();
                    state = MENU;
                }
                if (boardRenderer.isReadyBtnClicked(window) && player2Board.isPlacementReady()) {
                    player2Board.finishPlacement();
                    state = PLAYER_1_TURN;
                }
                if (boardRenderer.isJsonBtnClicked(window)) {
                    player2Board.generateRandomPlacement();
                    std::cout << "Loaded " << player2Board.getSelectedPlacementCells().size() << " placement cells for "
                              << player2.getName() << "." << std::endl;
                }
            } else if (state == PLAYER_1_TURN) {
                Coordinate clickedCell = boardRenderer.getClickedCell(window, player2Board, false);

                if (clickedCell.x != -1) {
                    bool hit = player2Board.shoot(clickedCell);
                    std::cout << "allShipsDestroyed: " << player2Board.allShipsDestroyed() << std::endl;
                    Move move;

                    move.coordinate = clickedCell;
                    move.hit = hit;

                    engine.addMove(move);

                    if (player2Board.allShipsDestroyed()) {
                        winner = player1.getName();
                        std::cout << winner << std::endl;
                        state = GAME_OVER;
                        return;
                    }

                    if (hit) {
                        state = PLAYER_1_TURN;
                    } else {
                        state = PLAYER_2_TURN;
                    }
                }

                if (boardRenderer.isBackBtnClicked(window)) {
                    resetGame();
                    state = MENU;
                }

                if (boardRenderer.isVisibilityBtnClicked(window)) {
                    player1Board.toggleShipVisibility();
                    std::cout << "VISIBLE: " << player1Board.areShipsVisible() << std::endl;
                }
            } else if (state == PLAYER_2_TURN) {
                Coordinate clickedCell = boardRenderer.getClickedCell(window, player1Board, true);

                if (clickedCell.x != -1) {
                    bool hit = player1Board.shoot(clickedCell);
                    std::cout << "allShipsDestroyed: " << player1Board.allShipsDestroyed() << std::endl;
                    Move move;

                    move.coordinate = clickedCell;
                    move.hit = hit;

                    engine.addMove(move);

                    if (player1Board.allShipsDestroyed()) {
                        winner = player2.getName();
                        state = GAME_OVER;
                        return;
                    }

                    if (hit) {
                        state = PLAYER_2_TURN;
                    } else {
                        state = PLAYER_1_TURN;
                    }
                }

                if (boardRenderer.isBackBtnClicked(window)) {
                    resetGame();
                    state = MENU;
                }

                if (boardRenderer.isVisibilityBtnClicked(window)) {
                    player2Board.toggleShipVisibility();
                    std::cout << "VISIBLE: " << player2Board.areShipsVisible() << std::endl;
                }
            } else if (state == GAME_OVER) {
                if (boardRenderer.isBackBtnClicked(window)) {
                    resetGame();
                    state = MENU;
                }
                return;
            }
        }
    }
}

void Window::update() {}

void Window::renderDarkModeButton() {
    const sf::Vector2u windowSize = window.getSize();
    darkModeButton.setFillColor(Colors::SuccessGreen());
    darkModeButton.setPosition(windowSize.x - darkModeButton.getSize().x - 20,
                               windowSize.y - darkModeButton.getSize().y - 20);
    darkModeButtonLabel.setString(Colors::darkMode ? "Lightmode" : "Darkmode");
    darkModeButtonLabel.setFillColor(Colors::Black());
    darkModeButtonLabel.setPosition(
        darkModeButton.getPosition().x +
            (darkModeButton.getSize().x - darkModeButtonLabel.getGlobalBounds().width) / 2.f,
        darkModeButton.getPosition().y +
            (darkModeButton.getSize().y - darkModeButtonLabel.getGlobalBounds().height) / 2.f - 4.f);

    window.draw(darkModeButton);
    window.draw(darkModeButtonLabel);
}

bool Window::isDarkModeButtonClicked() const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return darkModeButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void Window::renderBackground() {
    const sf::Vector2f size(window.getSize());
    sf::VertexArray background(sf::Quads, 4);

    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(size.x, 0);
    background[2].position = sf::Vector2f(size.x, size.y);
    background[3].position = sf::Vector2f(0, size.y);

    background[0].color = Colors::BackgroundTop();
    background[1].color = Colors::BackgroundTop();
    background[2].color = Colors::BackgroundBottom();
    background[3].color = Colors::BackgroundBottom();

    window.draw(background);
}

void Window::render() {
    window.clear(Colors::Menu());
    renderBackground();

    if (state == MENU) {
        menuRenderer.render(window);
    }

    if (state == PLACE_SHIPS_P1) {
        BoardArea playerArea = boardRenderer.getBoardArea(window, player1Board, true);
        boardRenderer.render(window, player1Board, player1.getName(), true, true, false);
        shipRenderer.render(window, player1Board, playerArea, true, true);
    }

    if (state == PLACE_SHIPS_P2) {
        BoardArea enemyArea = boardRenderer.getBoardArea(window, player2Board, false);
        boardRenderer.render(window, player2Board, player2.getName(), false, true, false);
        shipRenderer.render(window, player2Board, enemyArea, false, true);
    }

    if (state == PLAYER_1_TURN) {
        BoardArea playerArea = boardRenderer.getBoardArea(window, player1Board, true);
        BoardArea enemyArea = boardRenderer.getBoardArea(window, player2Board, false);
        boardRenderer.render(window, player1Board, player1.getName(), true, false, true);
        boardRenderer.render(window, player2Board, player2.getName(), false, false, false);
        shipRenderer.render(window, player1Board, playerArea, true, false);
        shipRenderer.render(window, player2Board, enemyArea, false, false);
    }

    if (state == PLAYER_2_TURN) {
        BoardArea playerArea = boardRenderer.getBoardArea(window, player1Board, true);
        BoardArea enemyArea = boardRenderer.getBoardArea(window, player2Board, false);
        boardRenderer.render(window, player1Board, player1.getName(), true, false, false);
        boardRenderer.render(window, player2Board, player2.getName(), false, false, true);
        shipRenderer.render(window, player1Board, playerArea, true, false);
        shipRenderer.render(window, player2Board, enemyArea, false, false);
    }

    if (state == GAME_OVER) {
        BoardArea playerArea = boardRenderer.getBoardArea(window, player1Board, true);
        BoardArea enemyArea = boardRenderer.getBoardArea(window, player2Board, false);
        boardRenderer.render(window, player1Board, player1.getName(), true, false, false);
        boardRenderer.render(window, player2Board, player2.getName(), false, false, false);
        shipRenderer.render(window, player1Board, playerArea, true, false);
        shipRenderer.render(window, player2Board, enemyArea, false, false);
        boardRenderer.renderGameOver(window, winner);
    }

    renderDarkModeButton();
    window.display();
}
