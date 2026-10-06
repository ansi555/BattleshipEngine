#pragma once

#include <SFML/Graphics.hpp>

namespace Colors {
inline bool darkMode = false;

inline const sf::Color& Menu() {
    static const sf::Color light(233, 241, 236);
    static const sf::Color dark(18, 24, 30);
    return darkMode ? dark : light;
}

inline const sf::Color& BackgroundTop() {
    static const sf::Color light(246, 250, 248);
    static const sf::Color dark(28, 36, 45);
    return darkMode ? dark : light;
}

inline const sf::Color& BackgroundBottom() {
    static const sf::Color light(223, 235, 228);
    static const sf::Color dark(16, 22, 28);
    return darkMode ? dark : light;
}

inline const sf::Color& Black() {
    static const sf::Color black(35, 40, 45);
    static const sf::Color white(235, 240, 245);
    return darkMode ? white : black;
}

inline const sf::Color& CellGrey() {
    static const sf::Color light(215, 220, 225);
    static const sf::Color dark(55, 62, 70);
    return darkMode ? dark : light;
}

inline const sf::Color& GridLine() {
    static const sf::Color light(100, 115, 130);
    static const sf::Color dark(140, 155, 170);
    return darkMode ? dark : light;
}

inline void toggleDarkMode() {
    darkMode = !darkMode;
}

inline const sf::Color& SuccessGreen() {
    static const sf::Color light(52, 199, 89);
    static const sf::Color dark(42, 160, 72);
    return darkMode ? dark : light;
}

inline const sf::Color& ErrorRed() {
    static const sf::Color light(230, 70, 70);
    static const sf::Color dark(180, 55, 55);
    return darkMode ? dark : light;
}

inline const sf::Color& WaterBlue() {
    static const sf::Color light(82, 172, 255);
    static const sf::Color dark(48, 115, 180);
    return darkMode ? dark : light;
}

inline const sf::Color& Purpur() {
    static const sf::Color light(153, 102, 255);
    static const sf::Color dark(110, 75, 185);
    return darkMode ? dark : light;
}

inline const sf::Color& OnyxHeart() {
    static const sf::Color light(22, 32, 42);
    static const sf::Color dark(10, 15, 20);
    return darkMode ? dark : light;
}

inline const sf::Color& SurroundingWater() {
    static const sf::Color light(0, 122, 204);
    static const sf::Color dark(0, 85, 145);
    return darkMode ? dark : light;
}
}  // namespace Colors
