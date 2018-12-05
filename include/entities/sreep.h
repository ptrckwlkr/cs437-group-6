#ifndef CSCI437_SREEP_H
#define CSCI437_SREEP_H


#include "events/event_collision.h"
#include "events/event_entity_damaged.h"
#include "entity.h"
#include "enemy.h"

#define SREEP_SIZE  55



class Sreep : public Enemy
{

public:
    Sreep(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void die();

private:
    void handleCollision(const EventCollision &event);

};


#endif //CSCI437_SREEP_H
