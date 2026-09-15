#pragma once

#include <SFML/Graphics.hpp>

namespace Colors {
inline bool darkMode = false;

inline const sf::Color& Menu() {
	static const sf::Color light(220, 236, 223);
	static const sf::Color dark(18, 27, 22);
	return darkMode ? dark : light;
}

inline const sf::Color& BackgroundTop() {
	static const sf::Color light(235, 246, 237);
	static const sf::Color dark(29, 42, 34);
	return darkMode ? dark : light;
}

inline const sf::Color& BackgroundBottom() {
	static const sf::Color light(220, 236, 223);
	static const sf::Color dark(18, 27, 22);
	return darkMode ? dark : light;
}

inline const sf::Color& Black() {
	static const sf::Color black(0, 0, 0);
	static const sf::Color white(220, 220, 220);
	return darkMode ? white : black;
}

inline const sf::Color& CellGrey() {
	static const sf::Color light(220, 220, 220);
	static const sf::Color dark(42, 42, 42);
	return darkMode ? dark : light;
}

inline const sf::Color& GridLine() {
	static const sf::Color light(170, 170, 170);
	static const sf::Color dark(100, 100, 100);
	return darkMode ? dark : light;
}

inline void toggleDarkMode() {
	darkMode = !darkMode;
}

inline const sf::Color& SuccessGreen() {
	static const sf::Color light(105, 170, 115);
	static const sf::Color dark(70, 120, 80);
	return darkMode ? dark : light;
}

inline const sf::Color& ErrorRed() {
	static const sf::Color light(208, 146, 146);
	static const sf::Color dark(130, 80, 80);
	return darkMode ? dark : light;
}

inline const sf::Color& WaterBlue() {
	static const sf::Color light(166, 205, 220);
	static const sf::Color dark(70, 110, 130);
	return darkMode ? dark : light;
}

inline const sf::Color& Purpur() {
	static const sf::Color light(183, 162, 208);
	static const sf::Color dark(100, 80, 125);
	return darkMode ? dark : light;
}

inline const sf::Color& OnyxHeart() {
	static const sf::Color light(52, 62, 58);
	static const sf::Color dark(30, 35, 32);
	return darkMode ? dark : light;
}

inline const sf::Color& SurroundingWater() {
	static const sf::Color light(80, 145, 180);
	static const sf::Color dark(35, 85, 115);
	return darkMode ? dark : light;
}
}  // namespace Colors
