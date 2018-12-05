#ifndef CSCI437_EVENT_VICTORY_H
#define CSCI437_EVENT_VICTORY_H

#include "event.h"

class EventVictory : public Event
{
public:
    EventVictory() : Event() {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}

};

#endif //CSCI437_EVENT_VICTORY_H
