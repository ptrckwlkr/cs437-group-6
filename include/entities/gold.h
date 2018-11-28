#ifndef CSCI437_GOLD_H
#define CSCI437_GOLD_H

#include <events/event_gold_collection.h>
#include <events/event_collision.h>
#include "entity.h"
#include "listener.h"

#define GOLD_SIZE 10

class Gold : public Entity
{

public:
    Gold(float x, float y);
    void move(Vector2D &dir, float delta) override {}

    void handleGoldCollection(const EventGoldCollection &event);
    void handleCollision(const EventCollision &event);

private:

};


#endif //CSCI437_GOLD_H
