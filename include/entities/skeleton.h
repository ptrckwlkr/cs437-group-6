#ifndef CSCI437_SKELETON_H
#define CSCI437_SKELETON_H


#include <events/event_collision.h>
#include "entity.h"
#include "event.h"

#define SKELETON_SIZE  20
#define SKELETON_SPEED 50
#define SKELETON_HEALTH 25


class Skeleton : public Entity
{

public:
    Skeleton(float x, float y);
    ~Skeleton();
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}

private:
    void handleCollision(const EventCollision &event);

};


#endif //CSCI437_SKELETON_H
