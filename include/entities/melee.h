#ifndef CSCI437_MELEE_H
#define CSCI437_MELEE_H

#include "events/event_collision.h"
#include "events/event_cycle_complete.h"
#include "entities/sword.h"
#include "entity.h"

class Melee: public Entity
{

private:
    void handleCollision(const EventCollision &event);
    void handleCycleComplete(const EventCycleComplete &event);
    Sword *sword;

public:
    Melee(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void setRadius(float r) {size = r;}
    void setDirection(Vector2D d);
    void move(Vector2D &dir, float delta) override {};

};


#endif //CSCI437_MELEE_H
