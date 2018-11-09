#ifndef CSCI437_GOLD_H
#define CSCI437_GOLD_H

#include "entity.h"
#include "listener.h"

#define GOLD_SIZE 10

class Gold : public Entity, public Listener
{

public:
    Gold(float x, float y);
    void move(Direction dir, float delta) override {} // Gold does not move
    void animate() override {} // Gold is not animated
    void HandleEvent(Event* event) override;

private:

};


#endif //CSCI437_GOLD_H
