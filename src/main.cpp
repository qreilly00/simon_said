//include classes and headers
#include "../inc/common.hpp"

#include "button/Button.hpp"
#include "simon/Simon.hpp"
#include "difficulty/Difficulty.hpp"
#include "timeUtil/TimeUtil.hpp"

//declare functions
std::vector<int> checkInput(std::string, int);
void incorrectInput(std::string);
//void showColors(std::vector<sf::Color> s1Colors, int col, float secs);

//initialise classes
Difficulty dif;
TimeUtil tm1;

Button b1;
Button b2;
Button b3;
Button b4;

Simon s1;

//main method
int main(int argc, char *argv[]) {

	//variables
	bool exit = 0;
	int difficulty = 0;
	int gameGo = 0;
	int col = 0;
	int dispCol = 1;
	int answerCount = 0;
	float timeAsSecs = 0;

	//check difficulty input at program start
	std::vector<int> out = checkInput(argv[1], argc);
	exit = out[0];
	difficulty = out[1];

	//create random color combo for game
	s1.generateResponse(difficulty);
	std::vector<sf::Color> response = s1.returnResponse();

	//colors for buttons
	std::vector<sf::Color> availableColors = s1.returnAvailableColors();

	//player answers
	std::vector<sf::Color> answerColors;

	//create basic display things
	sf::RenderWindow w(sf::VideoMode(500, 500), "Simon Said");
	sf::Event e;

	//set up font
	sf::Font font;
	if(!font.loadFromFile("animatic.ttf")) {
		exit = 1;
	}

	//setup text
	sf::Text text;
	text.setFont(font);
	text.setString("Hello world");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(s1.returnPosition());

	//button setup
	b1.setPosition(sf::Vector2f(0, 400));
	b2.setPosition(sf::Vector2f(101, 400));
	b3.setPosition(sf::Vector2f(202, 400));
	b4.setPosition(sf::Vector2f(303, 400));

	b1.setColor(availableColors[0]);
	b2.setColor(availableColors[1]);
	b3.setColor(availableColors[2]);
	b4.setColor(availableColors[3]);

	//simon setup
	s1.setPosition(sf::Vector2f(0, 100));

	//reset time for start
	tm1.setTime();

	//game loop
	while(exit != 1) {
		//close window
		while (w.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                exit = 1;

			//player now clicks the buttons for game
			if(dispCol == 0) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					sf::Vector2i localPosition = sf::Mouse::getPosition(w);

					sf::FloatRect bb1 = b1.returnShape().getGlobalBounds();
					sf::FloatRect bb2 = b2.returnShape().getGlobalBounds();
					sf::FloatRect bb3 = b3.returnShape().getGlobalBounds();
					sf::FloatRect bb4 = b4.returnShape().getGlobalBounds();

					if(bb1.contains(sf::Vector2f(localPosition))) {
						answerColors.push_back(availableColors[0]);
						s1.setColor(availableColors[0]);
					}
					if(bb2.contains(sf::Vector2f(localPosition))) {
						answerColors.push_back(availableColors[1]);
						s1.setColor(availableColors[1]);
					}
					if(bb3.contains(sf::Vector2f(localPosition))) {
						answerColors.push_back(availableColors[2]);
						s1.setColor(availableColors[2]);
					}
					if(bb4.contains(sf::Vector2f(localPosition))) {
						answerColors.push_back(availableColors[3]);
						s1.setColor(availableColors[3]);
					}
				}
			}
        }

		//show the player the game colors
		if(dispCol == 1) {
			tm1.setTime();
			timeAsSecs = timeAsSecs + tm1.getTime();

			if(timeAsSecs >= 1) {
				s1.setColor(response[col]);
				if(col == response.size()) {
					col = 0;
					dispCol = 0;
				} else {
					col++;
				}
				timeAsSecs = 0;
			}
			/*
			if(timeAsSecs >= dif.returnMediumFrequency() * 2 + 0.5) {
				timeAsSecs = 0;
				s1.setColor(response[col]);
			}

			if(timeAsSecs >= dif.returnMediumFrequency() * 2) {
				s1.setColor(sf::Color::Black);
			}
			*/
		} else {
			//s1.setColor(sf::Color::Black);
		}

		//check answer vector size
		if(answerColors.size() > response.size()) {
			exit = 1;
			std::cout << "Too many buttons pressed";
		} else if(answerColors.size() == response.size()/*answerCount == answerColors.size()*/) {

			for(int i = 0; i < answerColors.size(); i++) {
				if(answerColors[i] == response[i]) {
					answerCount++;
				}
			}
			if(answerCount == answerColors.size()) {
				exit = 1;
				std::cout << "Correct! Well done!" << std::endl;
			} else {
				exit = 1;
				std::cout << "Sorry! Wrong answer!" << std::endl;
			}
		}

		//draw entities
		w.clear(sf::Color::White);
        w.draw(b1.returnShape());
		w.draw(b2.returnShape());
		w.draw(b3.returnShape());
		w.draw(b4.returnShape());
		w.draw(s1.returnShape());
		//w.draw(text);
        w.display();
	}

	return 0;
}

std::vector<int> checkInput(std::string argv1, int argc) {
	//create variables
	std::vector<std::string> tmp = dif.returnOptions();
	std::vector<int> out(2);
	bool exit = 0;
	int difficulty = -1;


	if(argc == 1) { //check if there is enough input variables
		std::cout << "Please pass the desired Difficulty. The options are: " << std::endl;
		for(int i = 0; i < tmp.size(); i++) {
			std::cout << tmp[i] << std::endl;
		}
		exit = 1;
	} else if(argc > 1) { //accept input
		for(int i = 0; i < tmp.size(); i++) { //check the desired difficulty
			if(tmp[i] == argv1) {
				difficulty = i;
			}
		}

		if(difficulty == -1) { //the difficulty was not valid
			incorrectInput(argv1);
			exit = 1;
		} else {
			std::cout << "Success: " << argv1 << std::endl;
		}

	} else { //default case
		incorrectInput(argv1);
		exit = 1;
	}

	out[0] = exit;
	out[1] = difficulty;

	return out;
}

void incorrectInput(std::string input) { //print the incorrect difficulty option
	std::cout << "Incorrect Input: " << input << ". The options are: " << std::endl;
	for(int i = 0; i < dif.returnOptions().size(); i++) {
		std::cout << dif.returnOptions()[i] << std::endl;
	}
}
