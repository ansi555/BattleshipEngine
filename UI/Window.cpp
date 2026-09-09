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

    menuRenderer.init(font);
    boardRenderer.init(font);
    // shipRenderer.init(font);

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
            } else if (state == BOARD) {
                Coordinate clickedCell1 = boardRenderer.getClickedCell(window, player1Board, true);
                Coordinate clickedCell2 = boardRenderer.getClickedCell(window, player2Board, false);
                if (clickedCell1.x != -1) {
                    std::cout << "Clicked: Left  | " << clickedCell1.toString() << std::endl;
                }
                if (clickedCell2.x != -1) {
                    bool hit = player2Board.shoot(clickedCell2);

                    Move move;

                    move.coordinate = clickedCell2;
                    move.hit = hit;

                    engine.addMove(move);

                    std::cout

                        << clickedCell2.toString();

                    if (hit)

                    {
                        std::cout << " HIT";

                    }

                    else

                    {
                        std::cout << " MISS";
                    }

                    std::cout << std::endl;
                }

                if (boardRenderer.isBackBtnClicked(window)) {
                    resetGame();
                    state = MENU;
                }
            }
        }
    }
}

void Window::update() {}

void Window::render() {
    window.clear(Colors::Menu);

    if (state == MENU) {
        menuRenderer.render(window);
    }

    if (state == PLACE_SHIPS_P1) {
        BoardArea playerArea = boardRenderer.getBoardArea(window, player1Board, true);
        BoardArea enemyArea = boardRenderer.getBoardArea(window, player2Board, false);
        boardRenderer.render(window, player1Board, true);
        boardRenderer.render(window, player2Board, false);
        shipRenderer.render(window, player1Board, playerArea, true);
        shipRenderer.render(window, player2Board, enemyArea, false);
    }

    if (state == BOARD) {
        /* BoardArea playerArea = boardRenderer.getBoardArea(window, player1Board, true);
        BoardArea enemyArea = boardRenderer.getBoardArea(window, player2Board, false);
        boardRenderer.render(window, player1Board, true);
        boardRenderer.render(window, player2Board, false);
        shipRenderer.render(window, player1Board, playerArea, true);
        shipRenderer.render(window, player2Board, enemyArea, false); */
    }

    window.display();
}
