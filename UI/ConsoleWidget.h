#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class ConsoleWidget {
   private:
    sf::RectangleShape background;
    sf::Text inputText;
    sf::Text historyText;
    std::string currentInput;
    std::vector<std::string> history;
    bool commandReady = false;

   public:
    void init(sf::Font& font);
    void handleTextInput(const sf::Event& event);
    void handleKeyPressed(const sf::Event& event);
    bool hasCommandReady() const;
    std::string consumeCommand();
    void addHistory(const std::string& entry);
    std::string getBuffer() const;
    void render(sf::RenderWindow& window);
};
