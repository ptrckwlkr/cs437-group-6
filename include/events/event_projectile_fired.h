#ifndef CSCI437_EVENT_PROJECTILE_FIRED_H
#define CSCI437_EVENT_PROJECTILE_FIRED_H

#include "entities/entity.h"
#include "event.h"

class EventProjectileFired : public Event
{
public:
    explicit EventProjectileFired(long long entity_id) : Event(), entity_id(entity_id) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    long long getEntityID() const {return entity_id;}

private:
    long long entity_id;
};


#endif //CSCI437_EVENT_PROJECTILE_FIRED_H
