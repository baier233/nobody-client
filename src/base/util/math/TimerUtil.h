#pragma once
#include <ctime>
#include <iostream>

class TimerUtil {

public:
    static TimerUtil* GetInstance() {
        static auto instance = std::make_unique<TimerUtil>();
        return instance.get();
    }
    TimerUtil();
    bool elapsed(clock_t ms);
    bool elapsed(clock_t ms, clock_t* out_time);
    void reset();

private:

    clock_t lastMS;

    clock_t getCurrentTimeMS();

};