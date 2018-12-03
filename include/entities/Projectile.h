#ifndef CSCI437_PROJECTILE_H
#define CSCI437_PROJECTILE_H

#include <cmath>
#include "events/event_wall_collision.h"
#include "events/event_collision.h"
#include "entities/entity.h"
#include "SFML/System.hpp"

#define PROJECTILE_SPEED_DEFAULT        150
#define PROJECTILE_SIZE_DEFAULT         5

class Projectile: public Entity
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
    Projectile(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void set_maxRange(int mD) {maxRange = mD;}
    void set_direction(Vector2D vec) {direction = vec;}
    int get_maxRange() {return maxRange;}
    Vector2D  get_direction(){ return direction;}
    void move(Vector2D &dir, float delta) override;

    //The trail logic should probably be moved to ProjectileView but it can't be accessed from game graphics
    void updateTrail();

}; 



#endif //CSCI437_WEAPON_H

