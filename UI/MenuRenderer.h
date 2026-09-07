#pragma once

#include <SFML/Graphics.hpp>

class MenuRenderer
{
public:
    sf::Text title;
    sf::Text boardBtn;

    void init(sf::Font &font);

    void render(sf::RenderWindow &window);
};
