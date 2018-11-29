#ifndef CSCI437_PROJECTILE_H
#define CSCI437_PROJECTILE_H

#include <events/event_wall_collision.h>
#include "entity.h"
#include "event.h"
#include "math.h"
#include "SFML/System.hpp"
#include "vector2d.h"

#define PROJECTILE_SPEED_DEFAULT        75
#define PROJECTILE_SIZE_DEFAULT         5

class Projectile: public Entity
{

private:
    int damage;
    int maxRange;
    float traveled;

    void handleWallCollision(const EventWallCollision &event);

protected:
    Vector2D direction = VEC_NONE;



public:
    Projectile(float x, float y);
    ~Projectile();
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}

    virtual void update(double deltaMs) {};

    void set_damage(int mD) {damage = mD;}

    void set_maxRange(int mD) {maxRange = mD;}

    void set_speed (int s) {speed = s;}

    void set_direction(Vector2D vec) {direction = vec;}

    float get_travaled() {return traveled;}

    int get_maxRange() {return maxRange;}

    Vector2D  get_direciton(){ return direction;}

    void move(Vector2D &dir, float delta) override;

}; 



#endif //CSCI437_WEAPON_H

