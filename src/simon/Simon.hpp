#ifndef SIMON_HPP
#define SIMON_HPP

#include "../../inc/common.hpp"

class Simon {
private:

	sf::CircleShape shape;
	sf::Color shapeColor;
	std::vector<std::string> shapeResponse;

public:

	Simon();

	sf::CircleShape returnShape();
	sf::Color returnColor();
	sf::Vector2f returnPosition();
	std::vector<std::string> returnResponse();
	float returnRadius();

	void generateResponse(int difficulty);

	void setPosition(sf::Vector2f in);

};

#endif
