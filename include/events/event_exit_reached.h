#ifndef CSCI437_EVENT_EXIT_REACHED_H
#define CSCI437_EVENT_EXIT_REACHED_H

#include "event.h"

class EventExitReached : public Event
{
public:
    EventExitReached() : Event() {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}

};


#endif //CSCI437_EVENT_EXIT_REACHED_H
