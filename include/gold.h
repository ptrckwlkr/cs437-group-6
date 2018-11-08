#ifndef CSCI437_GOLD_H
#define CSCI437_GOLD_H

#include "entity.h"

#define GOLD_SIZE 10

class Gold : public Entity
{

public:
    Gold(float x, float y);
    void move(Direction dir, float delta) {} // Gold does not move
    void animate() {} // Gold is not animated
    void HandleEvents(Event* event);

private:

};


#endif //CSCI437_GOLD_H
