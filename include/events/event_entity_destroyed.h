#ifndef CSCI437_EVENT_ENTITY_DESTROYED_H
#define CSCI437_EVENT_ENTITY_DESTROYED_H

#include "entity.h"
#include "event.h"

class EventEntityDestroyed : public Event
{

public:
    explicit EventEntityDestroyed(long long entity_id, EntityType type, Vector2D position) : Event(), entity_id(entity_id), type(type), position(position) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    long long getEntityID() const {return entity_id;}
    EntityType getType() const {return type;}
    Vector2D getPosition() const {return position;}

private:
    long long entity_id;
    EntityType type;
    Vector2D position;

};


#endif //CSCI437_EVENT_ENTITY_DESTROYED_H
