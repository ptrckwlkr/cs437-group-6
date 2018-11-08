#ifndef CSCI437_ENEMY_H
#define CSCI437_ENEMY_H

#include "event.h"
#include "entity.h"

class Enemy: public Entity{

    private: 
        int health;
        int mana;

    public: 
        Enemy();

        ~Enemy();
        virtual void update(double deltaMs) = 0;
        void set_position(Position new_pos);

        //handles events 
        void HandleEvents( Event* event);
        ///if eventid = "walk"
        //move

        int get_health(){return health;}

        void move(Direction dir, float delta);

}; 

#endif //CSCI437_ENEMY_H