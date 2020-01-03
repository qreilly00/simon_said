#include "../inc/common.hpp"

#include "button/Button.hpp"
#include "simon/Simon.hpp"
#include "difficulty/Difficulty.hpp"
#include "timeUtil/TimeUtil.hpp"

std::vector<int> checkInput(std::string, int);
void incorrectInput(std::string);
//void showColors(std::vector<sf::Color> s1Colors, int col, float secs);

Difficulty dif;
TimeUtil tm1;

Button b1;
Button b2;
Button b3;
Button b4;

Simon s1;

int main(int argc, char *argv[]) {
	bool exit = 0;
	int difficulty = 0;
	int gameGo = 0;
	int col = 0;
	float timeAsSecs;
	int dispCol = 1;

	b1.setPosition(sf::Vector2f(0, 400));
	b2.setPosition(sf::Vector2f(101, 400));
	b3.setPosition(sf::Vector2f(202, 400));
	b4.setPosition(sf::Vector2f(303, 400));
	s1.setPosition(sf::Vector2f(200, 100));

	std::vector<int> out = checkInput(argv[1], argc);
	exit = out[0];
	difficulty = out[1];

	s1.generateResponse(difficulty);
	std::vector<sf::Color> response = s1.returnResponse();

	sf::RenderWindow w(sf::VideoMode(500, 500), "Simon Said");
	sf::Event e;

	sf::Font font;

	if(!font.loadFromFile("animatic.ttf")) {
		exit = 1;
	}

	sf::Text text;
	text.setFont(font);
	text.setString("Hello world");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(s1.returnPosition());

	b1.setColor(response[0]);
	b2.setColor(response[1]);
	b3.setColor(response[2]);
	b4.setColor(response[3]);

	//std::cout << response.size();

	tm1.setTime();

	while(exit != 1) {
		while (w.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                exit = 1;
        }

		if(dispCol == 1) {
			tm1.setTime();
			timeAsSecs = timeAsSecs + tm1.getTime();

			/*
			if(timeAsSecs >= dif.returnMediumFrequency() * 2 + 0.5) {
				timeAsSecs = 0;
				s1.setColor(response[col]);
			}

			if(timeAsSecs >= dif.returnMediumFrequency() * 2) {
				s1.setColor(sf::Color::Black);
			}
			*/

			if(timeAsSecs >= 1) {
				s1.setColor(response[col]);
				if(col + 1 == response.size()) {
					col = 0;
					dispCol = 0;
				} else {
					col++;
				}

				timeAsSecs = 0;
			}


		} else {
			s1.setColor(sf::Color::Black);
		}

		w.clear(sf::Color::White);
        w.draw(b1.returnShape());
		w.draw(b2.returnShape());
		w.draw(b3.returnShape());
		w.draw(b4.returnShape());
		w.draw(s1.returnShape());
		w.draw(text);
        w.display();
	}

	return 0;
}

std::vector<int> checkInput(std::string argv1, int argc) {
	std::vector<std::string> tmp = dif.returnOptions();
	//std::cout << "tmp: " << tmp[2] << std::endl;

	std::vector<int> out(2);
	bool exit = 0;
	int difficulty = -1;

	if(argc == 1) {
		std::cout << "Please pass the desired Difficulty. The options are: " << std::endl;
		for(int i = 0; i < tmp.size(); i++) {
			std::cout << tmp[i] << std::endl;
		}
		exit = 1;
	} else if(argc > 1) {
		for(int i = 0; i < tmp.size(); i++) {
			if(tmp[i] == argv1) {
				difficulty = i;
			}
		}

		if(difficulty == -1) {
			incorrectInput(argv1);
			exit = 1;
		} else {
			std::cout << "Success: " << argv1 << std::endl;
		}

	} else {
		incorrectInput(argv1);
		exit = 1;
	}

	out[0] = exit;
	out[1] = difficulty;

	return out;
}

void incorrectInput(std::string input) {
	std::cout << "Incorrect Input: " << input << ". The options are: " << std::endl;
	for(int i = 0; i < dif.returnOptions().size(); i++) {
		std::cout << dif.returnOptions()[i] << std::endl;
	}
}
