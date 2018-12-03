#ifndef CSCI437_GHOST_H
#define CSCI437_GHOST_H

#include "events/event_collision.h"
#include "events/event_entity_damaged.h"
#include "entity.h"
#include "enemy.h"


#define GHOST_SIZE  15

class Ghost : public Enemy
{
public:
    Ghost(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void die();



private:
    void handleCollision(const EventCollision &event);

};


#endif //CSCI437_GHOST_H
