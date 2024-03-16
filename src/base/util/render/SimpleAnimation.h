#pragma once
#include <chrono>
#include <cmath>

class SimpleAnimation {
private:
    float value;
    std::chrono::milliseconds lastMS;

public:
    SimpleAnimation(float value) : value(value), lastMS(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())) {}

    void setAnimation(float value, double speed) {
        auto currentMS = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        auto delta = currentMS - this->lastMS;
        this->lastMS = currentMS;

        double deltaValue = 0.0;

        if (speed > 28) {
            speed = 28;
        }

        if (speed != 0.0) {
            deltaValue = std::abs(value - this->value) * 0.35f / (10.0 / speed);
        }

        this->value = calculateCompensation(value, this->value, deltaValue, delta.count());
    }

    float getValue() const {
        return value;
    }

    void setValue(float value) {
        this->value = value;
    }

private:
    float calculateCompensation(const float target, float current, const double speed, long delta) {
        const float diff = current - target;

        double add = (delta * (speed / 50));

        if (diff > speed) {
            if (current - add > target) {
                current -= add;
            }
            else {
                current = target;
            }
        }
        else if (diff < -speed) {
            if (current + add < target) {
                current += add;
            }
            else {
                current = target;
            }
        }
        else {
            current = target;
        }

        return current;
    }
};