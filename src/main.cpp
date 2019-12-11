#include "../inc/common.hpp"

#include "button/Button.hpp"
#include "simon/Simon.hpp"
#include "difficulty/Difficulty.hpp"

std::vector<int> checkInput(std::string, int);
void incorrectInput(std::string);

Difficulty dif;

Button b1;
Button b2;
Button b3;
Button b4;

Simon s1;

int main(int argc, char *argv[]) {
	bool exit = 0;
	int difficulty = 0;

	b1.setPosition(sf::Vector2f(0, 500));
	b2.setPosition(sf::Vector2f(101, 500));
	b3.setPosition(sf::Vector2f(202, 500));
	b4.setPosition(sf::Vector2f(303, 500));
	s1.setPosition(sf::Vector2f(200, 200));

	std::vector<int> out = checkInput(argv[1], argc);
	exit = out[0];
	difficulty = out[1];

	s1.generateResponse(difficulty);
	//std::vector<sf::Color> response = s1.returnResponse();

	sf::RenderWindow w(sf::VideoMode(900, 800), "Simon Said");
	sf::Event e;

	while(exit != 1) {
		while (w.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                exit = 1;
        }

		w.clear(sf::Color::Cyan);
        w.draw(b1.returnShape());
		w.draw(b2.returnShape());
		w.draw(b3.returnShape());
		w.draw(b4.returnShape());
		w.draw(s1.returnShape());
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
