#ifndef DIFFICULTY_HPP
#define DIFFICULTY_HPP

#include "../../inc/common.hpp"

class Difficulty {
private:

	int mediumCount;
	int mediumFrequency;

	std::vector<std::string> options;

public:

	Difficulty();

	int returnMediumCount();
	int returnMediumFrequency();

	std::vector<std::string> returnOptions();

};

#endif
