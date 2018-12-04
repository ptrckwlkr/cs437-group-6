#ifndef CSCI437_ORC_H
#define CSCI437_ORC_H

#include "events/event_collision.h"
#include "events/event_entity_damaged.h"
#include "entity.h"
#include "enemy.h"


#define ORC_SIZE  15

class Orc : public Enemy
{
public:
    Orc(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void die();



private:
    void handleCollision(const EventCollision &event);

};


#endif //CSCI437_ORC_H
