#ifndef CSCI437_EXIT_H
#define CSCI437_EXIT_H

#include "entities/entity.h"
#include "events/event_collision.h"

#define EXIT_SIZE 15

class Exit : public Entity
{

public:
    Exit(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void move(Vector2D &dir, float delta) override {}

private:
    void handleCollision(const EventCollision &event);

};

#endif //CSCI437_EXIT_H
