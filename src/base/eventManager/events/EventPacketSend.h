#pragma once


#include "../AbstractEvent.h"

class EventPacketSend : public Event<EventPacketSend> {
public:
    EventPacketSend(const char* buffer) : buffer(buffer) {}

    const char* getPackets() const { return this->buffer; }

private:
    const char* buffer;
};