#ifndef CSCI437_SKELETON_H
#define CSCI437_SKELETON_H

#include "entity.h"
#include "event.h"

#define SKELETON_SIZE 10

class Skeleton : public Entity
{

public:
    Skeleton(float x, float y);
    void move(Direction dir, float delta) override;
    void HandleEvent(Event *event) override;

private:

};


#endif //CSCI437_SKELETON_H
