#ifndef CSCI437_SREEP_PROJECTILE_H
#define CSCI437_SREEP_PROJECTILE_H


#include <cmath>
#include "events/event_wall_collision.h"
#include "events/event_collision.h"
#include "entities/entity.h"

#define SREEP_PROJECTILE_SPEED_DEFAULT        200
#define SREEP_PROJECTILE_SIZE_DEFAULT         7

class SreepProjectile: public Entity
{

private:
    int maxRange;
    float traveled;
    bool hit;

    void handleWallCollision(const EventWallCollision &event);
    void handleCollision(const EventCollision &event);

protected:
    Vector2D direction = VEC_NONE;



public:
    SreepProjectile(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void set_maxRange(int mD) {maxRange = mD;}
    void set_direction(Vector2D vec) {direction = vec;}
    int get_maxRange() {return maxRange;}
    Vector2D  get_direction(){ return direction;}
    void move(Vector2D &dir, float delta) override;

};


#endif //CSCI437_SREEP_PROJECTILE_H
