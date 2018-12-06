#ifndef CSCI437_POTION_H
#define CSCI437_POTION_H

#include "events/event.h"
#include "entities/entity.h"
#include "events/event_collision.h"

#define POTION_SIZE 10

class Potion : public Entity
{

public:
    Potion(float x, float y);

    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void move(Vector2D &dir, float delta) override {}

    unsigned int type_num;

private:
    void handleCollision(const EventCollision &event);

};

#endif //CSCI437_POTION_H
