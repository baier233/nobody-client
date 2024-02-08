#include "TimerUtil.h"

TimerUtil::TimerUtil() {
    this->reset();
}

bool TimerUtil::elapsed(clock_t ms) {
    if ((this->getCurrentTimeMS() - this->lastMS) > ms) return true;
    return false;
}

bool TimerUtil::elapsed(clock_t ms, clock_t* out_time) {

    long interval = this->getCurrentTimeMS() - this->lastMS;
    *out_time = (interval < 0 ? 0 : interval);
    if (interval > ms) return true;
    return false;
}

void TimerUtil::reset() {
    this->lastMS = this->getCurrentTimeMS();
}

clock_t TimerUtil::getCurrentTimeMS() {
    return clock();
}