#ifndef CSCI437_EVENT_CYCLE_COMPLETE_H
#define CSCI437_EVENT_CYCLE_COMPLETE_H

#include "event.h"

class EventCycleComplete : public Event
{
public:
    EventCycleComplete(float delta) : Event(), delta(delta) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    float getDelta() const {return delta;}

private:
    float delta;
};

#endif //CSCI437_EVENT_CYCLE_COMPLETE_H
