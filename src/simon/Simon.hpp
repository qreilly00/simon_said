#ifndef SIMON_HPP
#define SIMON_HPP

#include "../../inc/common.hpp"

class Simon {
private:

	sf::CircleShape shape;
	sf::Color shapeColor;
	std::vector<sf::Color> availableColors;
	std::vector<sf::Color> shapeResponse;

	int medFrequency;
	int medCount;

public:

	Simon();

	sf::CircleShape returnShape();
	sf::Color returnColor();
	sf::Vector2f returnPosition();
	float returnRadius();

	void generateResponse(int difficulty);
	std::vector<sf::Color> returnResponse();

	void setPosition(sf::Vector2f in);

};

#endif
