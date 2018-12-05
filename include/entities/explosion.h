#ifndef CSCI437_EXPLOSION_H
#define CSCI437_EXPLOSION_H


#include "entity.h"

class Explosion : public Entity
{

public:
    Explosion(float x, float y) : Entity(x, y, 0) {};
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void move(Vector2D &dir, float delta) override {}

};


#endif //CSCI437_EXPLOSION_H
