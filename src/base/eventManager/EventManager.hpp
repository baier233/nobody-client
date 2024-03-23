#pragma once
#include <windows.h>
#include "AbstractEvent.h"
#include <functional>

#define BindHandler(_Event, _Handler) EventManager::getInstance().reg<_Event>(_Handler);
#define BindClassHandler(_Event, _ClassPtr, _Handler) EventManager::getInstance().reg<_Event>(std::bind(&_Handler, _ClassPtr, std::placeholders::_1))

class EventManager {
public:
    static EventManager& getInstance() {
        static EventManager inst;
        return inst;
    }
    template <class EventType>
    using Handler = std::function<void(const EventType&)>;

    template <class EventType>
    void reg(Handler<EventType> handler) {
        if (EventType::getType() >= this->handlers.size())
            this->handlers.resize(EventType::getType() + 1);
        this->handlers[EventType::getType()].push_back(
            HandlerWrapper<EventType>(handler));
    }

    template <class EventType>
    void call(const EventType& event) {
        try
        {
            if (EventType::getType() >= this->handlers.size())
                this->handlers.resize(EventType::getType() + 1);
            for (auto& handler : this->handlers[event.getType()]) {
                handler(event);
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
      
    }

    template <class EventType>
    class HandlerWrapper {
    public:
        HandlerWrapper(Handler<EventType> handler) : handler(handler) {}
        void operator()(const AbstractEvent& event) { this->handler(static_cast<const EventType&>(event)); }
        Handler<EventType> handler;
    };

private:
    std::vector<std::vector<Handler<AbstractEvent>>> handlers;

};

