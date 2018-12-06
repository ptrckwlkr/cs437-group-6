#ifndef CSCI437_EVENT_LEVEL_COMPLETE_H
#define CSCI437_EVENT_LEVEL_COMPLETE_H

#include "event.h"

class EventLevelComplete : public Event
{
public:
    EventLevelComplete(int level) : Event(), level(level) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    const int getLevel() const {return level;}

private:
    int level;

};

#endif //CSCI437_EVENT_LEVEL_COMPLETE_H
