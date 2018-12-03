#ifndef CSCI437_EVENT_ENTITY_DAMAGED_H
#define CSCI437_EVENT_ENTITY_DAMAGED_H

#include "event.h"

class EventEntityDamaged : public Event
{
public:
    EventEntityDamaged(long long entity_id, long long type) : Event(), entity_id(entity_id), type(type) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    long long getEntityID() const {return entity_id;}
    long long getEntityType() const {return type;}

private:
    long long entity_id;
    long long type;
};


#endif //CSCI437_EVENT_ENTITY_DESTROYED_H
