#pragma once
#include <Windows.h>
class AbstractEvent {

        public:
        inline static unsigned int typeCount = 0;
        virtual ~AbstractEvent() = default;

};

template <class EventType>
class Event : public AbstractEvent {

public:
    static unsigned int getType() {
        static unsigned int etype = AbstractEvent::typeCount++;
        return etype;
    }

};


