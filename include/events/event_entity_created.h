#ifndef CSCI437_EVENT_ENTITY_CREATED_H
#define CSCI437_EVENT_ENTITY_CREATED_H


#include "entities/entity.h"
#include "event.h"

class EventEntityCreated : public Event
{

public:
    explicit EventEntityCreated(Entity *entity) : Event(), entity(entity) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    Entity &getEntity() const {return *entity;}

private:
    Entity *entity;

};


#endif //CSCI437_EVENT_ENTITY_CREATED_H
