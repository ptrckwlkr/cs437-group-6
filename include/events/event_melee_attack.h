#ifndef CSCI437_EVENT_MELEE_ATTACK_H
#define CSCI437_EVENT_MELEE_ATTACK_H

#include "entities/entity.h"
#include "event.h"

class EventMeleeAttack : public Event
{
public:
    explicit EventMeleeAttack(long long entity_id) : Event(), entity_id(entity_id) {};
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    long long getEntityID() const {return entity_id;}

private:
    long long entity_id;
};


#endif //CSCI437_EVENT_MELEE_ATTACK_H
