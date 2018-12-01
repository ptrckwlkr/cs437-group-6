#ifndef CSCI437_EVENT_ENTITY_DAMAGED_H
#define CSCI437_EVENT_ENTITY_DAMAGED_H

#include "entities/entity.h"
#include "event.h"

class EventEntityDamaged : public Event
{
public:
    explicit EventEntityDamaged(long long entity_id, EntityType type) : Event(), entity_id(entity_id), type(type) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    long long getEntityID() const {return entity_id;}
    EntityType getType() const {return type;}

private:
    long long entity_id;
    EntityType type;
};


#endif //CSCI437_EVENT_ENTITY_DESTROYED_H
