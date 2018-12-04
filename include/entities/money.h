#ifndef CSCI437_MONEY_H
#define CSCI437_MONEY_H


#include "entity.h"

class Money : public Entity
{

public:
    Money(float x, float y) : Entity(x, y, 0) {};
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void move(Vector2D &dir, float delta) override {}

};


#endif //CSCI437_MONEY_H
