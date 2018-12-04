#ifndef CSCI437_SMOKE_H
#define CSCI437_SMOKE_H


#include "entity.h"

class Smoke : public Entity
{

public:
    Smoke(float x, float y) : Entity(x, y, 0) {};
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void move(Vector2D &dir, float delta) override {}

};


#endif //CSCI437_SMOKE_H
