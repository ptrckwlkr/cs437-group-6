#ifndef CSCI437_BLOOD_H
#define CSCI437_BLOOD_H


#include "entity.h"

class Blood : public Entity
{

public:
    Blood(float x, float y) : Entity(x, y, 0) {};
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void move(Vector2D &dir, float delta) override {}

};


#endif //CSCI437_BLOOD_H
