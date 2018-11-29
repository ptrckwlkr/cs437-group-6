#ifndef CSCI437_EVENT_WALL_COLLISION_H
#define CSCI437_EVENT_WALL_COLLISION_H

#include "entities/entity.h"
#include "event.h"

class EventWallCollision : public Event
{
public:
    EventWallCollision(Entity *entity) : Event(), entity(entity) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    Entity &getEntity() const {return *entity;}

private:
    Entity *entity;
};


#endif //CSCI437_EVENT_WALL_COLLISION_H
