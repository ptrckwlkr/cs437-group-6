#ifndef CSCI437_BOSS_H
#define CSCI437_BOSS_H


#include <events/event_collision.h>
#include "enemy.h"

#define BOSS_SIZE  20

class Boss : public Enemy
{
public:
    Boss(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void die();
    void attack(float delta, float delta_threshold, Vector2D dir);



private:
    void handleCollision(const EventCollision &event);

    float delta_sum;

};



#endif //CSCI437_BOSS_H
