#include "Simon.hpp"

void Simon::generateResponse(int difficulty) {
	std::vector<int> values(2);

	if(difficulty == 1) {
		values[0] = medFrequency;
		values[1] = medCount;
	}

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, availableColors.size());

	for(int i = 0; i < values[1]; i++) {
		shapeResponse.push_back(availableColors[dist(mt)]);
		//std::cout << shapeResponse[i] << std::endl;
	}
}
