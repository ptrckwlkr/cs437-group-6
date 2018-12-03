#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include <memory>
#include "entities/entity.h"

#define PLAYER_SIZE  15

class Player: public Entity
{

private:
    float max_health;
    float mana;
    float max_mana;
    float mana_regen;

public:
		Player(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}

    void set_max_health(float max) {max_health = max;}
    void set_mana(float m) {mana = m;}
    void set_max_mana(float max) {max_mana = max;}
    void set_mana_regen(float rate) {mana_regen = rate;}

    const float get_max_health() const {return max_health;}
    const float get_mana() const {return mana;}
    const float get_max_mana() const {return max_health;}
    const float get_mana_regen() const {return mana;}

    void attack(Vector2D &dir, float delta);
    void die() override;

    //used to prevent more than one projectile firing each frame (assuming 60fps)
    //NOTE THIS CAN BE CHANGED TO SIMULATE DIFFERENT WEAPON SPEED
    float delta_threshold = (float)(10 / 60.0);
    float delta_sum;

};

#endif //CSCI437_PLAYER_H