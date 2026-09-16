#include "ConsoleWidget.h"

#include "../Assets/Colors.h"

void ConsoleWidget::init(sf::Font& font) {
    background.setSize(sf::Vector2f(1200.f, 140.f));
    background.setPosition(sf::Vector2f(200.f, 730.f));
    background.setFillColor(Colors::CellGrey());
    background.setOutlineColor(Colors::Black());
    background.setOutlineThickness(2.f);

    historyText.setFont(font);
    historyText.setCharacterSize(18);
    historyText.setFillColor(Colors::Black());
    historyText.setPosition(220.f, 740.f);

    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(Colors::Black());
    inputText.setPosition(220.f, 835.f);

    currentInput.clear();
}

void ConsoleWidget::handleTextInput(const sf::Event& event) {
    if (event.text.unicode < 32 || event.text.unicode > 126) {
        return;
    }
    currentInput += static_cast<char>(event.text.unicode);
}

void ConsoleWidget::handleKeyPressed(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::BackSpace) {
        if (!currentInput.empty()) {
            currentInput.pop_back();
        }
    }
    if (event.key.code == sf::Keyboard::Enter) {
        commandReady = true;
    }
}

bool ConsoleWidget::hasCommandReady() const {
    /* return !currentInput.empty() && currentInput.back() == '\n'; */
    return commandReady;
}

std::string ConsoleWidget::consumeCommand() {
    std::string command = currentInput;
    if (!command.empty() && command.back() == '\n') {
        command.pop_back();
    }
    addHistory("> " + command);
    currentInput.clear();
    commandReady = false;
    return command;
}

void ConsoleWidget::addHistory(const std::string& entry) {
    history.push_back(entry);
    while (history.size() > 5) {
        history.erase(history.begin());
    }
}

std::string ConsoleWidget::getBuffer() const {
    return currentInput;
}

void ConsoleWidget::render(sf::RenderWindow& window) {
    std::string historyString;
    for (const std::string& line : history) {
        historyString += line;
        historyString += "\n";
    }
    historyText.setString(historyString);
    inputText.setString("> " + currentInput);
    window.draw(background);
    window.draw(historyText);
    window.draw(inputText);
}
