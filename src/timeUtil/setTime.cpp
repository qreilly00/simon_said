#include "TimeUtil.hpp"

void TimeUtil::setTime() {
	dt = clock.restart();
	dtAsSeconds = dt.asSeconds();
}
