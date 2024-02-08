
#include "../base.h"

Chronometer::Chronometer(std::chrono::milliseconds everyXms)
{
	setEvery(everyXms);
}

bool Chronometer::isElapsed()
{
	std::chrono::steady_clock::time_point timerNow = std::chrono::steady_clock::now();
	if (duration_cast<std::chrono::milliseconds>(timerNow - timerBegin) >= targetMs) {
		timerBegin = timerNow;
		return true;
	}
	return false;
}	

void Chronometer::setEvery(std::chrono::milliseconds everyXms)
{
	timerBegin = std::chrono::steady_clock::now();
	targetMs = everyXms;
}