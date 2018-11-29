#ifndef CSCI437_SKELETON_H
#define CSCI437_SKELETON_H

#include "entity.h"
#include "event.h"

#define SKELETON_SIZE  15
#define SKELETON_SPEED 50

class Skeleton : public Entity
{

public:
    Skeleton(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}

private:

};


#endif //CSCI437_SKELETON_H
