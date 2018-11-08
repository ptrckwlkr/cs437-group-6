#ifndef CSCI437_PROJECTILE_H
#define CSCI437_PROJECTILE_H

#include "entity.h"
#include "event.h"

class Projectile: public Entity{

    private: 
    int maxDamage;
    int curDamage;
    int maxRange;


    public: 
        Projectile();

        ~Projectile();
        virtual void update(double deltaMs) = 0;

        void set_position(Position new_pos);
        //should be set in position of player

        //handles events 
        void HandleEvents( Event* event);
        ///if eventid = "attack"

        void attack(Direction dir, float delta);

}; 



#endif //CSCI437_WEAPON_H

