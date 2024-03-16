#pragma once


#include "../AbstractEvent.h"

class EventKey : public Event<EventKey> {
public:
    EventKey(int key) : key(key) {}

    int getKey() const { return this->key; }

private:
    int key;
};