#include "Window.h"

#include <iostream>

Window::Window() {
    window.create(sf::VideoMode(1600, 900), "BattleshipGame");

    state = MENU;
    font.loadFromFile("Assets/DejaVuSans.ttf");

    menuRenderer.init(font);
    boardRenderer.init(font);
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
                    state = BOARD;
                }
            }

            if (state == BOARD) {
                Coordinate clickedCell = boardRenderer.getClickedCell(window, player2Board, false);
                if (clickedCell.x != -1) {
                    std::cout << "Clicked: " << clickedCell.toString() << std::endl;
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

    if (state == BOARD) {
        boardRenderer.render(window, player1Board, true);
        boardRenderer.render(window, player2Board, false);
    }

    window.display();
}
