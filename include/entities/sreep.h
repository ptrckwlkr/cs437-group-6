#ifndef CSCI437_SREEP_H
#define CSCI437_SREEP_H


#include "events/event_collision.h"
#include "events/event_entity_damaged.h"
#include "entity.h"
#include "enemy.h"

#define SREEP_SIZE  55



class Sreep : public Enemy
{

public:
    Sreep(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void fire_all_dirs();
    void fire_at_player();
    bool is_firing() {return firing;}
    void set_firing(bool f) {firing = f;}
    void die();

private:
    void handleCollision(const EventCollision &event);
    bool firing = false;

};


#endif //CSCI437_SREEP_H
