#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../../inc/common.hpp"

class Button {
private:

	sf::CircleShape shape;
	sf::Color shapeColor;
	std::string shapeResponse;

public:

	Button();

	sf::CircleShape returnShape();
	sf::Color returnColor();
	std::string returnResponse();
	sf::Vector2f returnPosition();
	float returnRadius();

	void setPosition(sf::Vector2f in);
	void setColor(sf::Color in);

};

#endif
