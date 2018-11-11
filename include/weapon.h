#ifndef CSCI437_WEAPON_H
#define CSCI437_WEAPON_H

#include "entity.h"
#include "event.h"

class Weapon {

    private: 
    int maxDamage;
    int curDamage;
    int maxRange;
    Position pos;
    int dir;


    public: 
        Weapon();

        ~Weapon();

        void set_position(Position new_pos);
        //should be set in position of player

        void set_maxDamage( int maxD);
        
        void set_maxRange( int maxR);

        int get_curDamage( int curD){ return this->curDamage;}

        //handles events 
        void HandleEvents( Event* event);
        ///if eventid = "attack"

        void attack(Direction dir, float delta);

        enum WeaponType{
            Range, 
            Melee
        };

}; 



#endif //CSCI437_WEAPON_H