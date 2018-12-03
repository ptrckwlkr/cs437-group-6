#ifndef CSCI437_SWORD_H
#define CSCI437_SWORD_H

#include "entity.h"

class Sword : public Entity
{

public:
    Sword(float x, float y) : Entity(x, y, 0) {};
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void move(Vector2D &dir, float delta) override {}
    void setAngle(Vector2D dir) {angle = atan2f(dir.y, dir.x) * 180 / (float)3.14159265;}
    float getAngle() const {return angle;}

private:
    float angle;

};



#endif //CSCI437_SWORD_H
