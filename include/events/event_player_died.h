#ifndef CSCI437_EVENT_PLAYER_DIED_H
#define CSCI437_EVENT_PLAYER_DIED_H

#include "entities/entity.h"
#include "event.h"

class EventPlayerDied : public Event
{

public:
    EventPlayerDied() : Event() {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}

};

#endif //CSCI437_EVENT_PLAYER_DIED_H
