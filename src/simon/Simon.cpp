#include "Simon.hpp"

Simon::Simon() {
	shape.setRadius(50.f);
	shape.setFillColor(sf::Color::Black);

	medFrequency = 1;
	medCount = 4;
	
	availableColors.push_back(sf::Color::White);
	availableColors.push_back(sf::Color::Red);
	availableColors.push_back(sf::Color::Green);
	availableColors.push_back(sf::Color::Blue);
	availableColors.push_back(sf::Color::Yellow);
	availableColors.push_back(sf::Color::Magenta);
	availableColors.push_back(sf::Color::Cyan);
}
