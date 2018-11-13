#ifndef CSCI437_PROJECTILE_H
#define CSCI437_PROJECTILE_H

#include "entity.h"
#include "event.h"

class Projectile: public Entity
{

    private: 
    int maxDamage;
    int curDamage;
    int maxRange;


    public: 
        Projectile(float x, float y, float size);

        ~Projectile();
        virtual void update(double deltaMs) = 0;

        //handles events 
        void HandleEvents( Event* event);
        ///if eventid = "attack"

        void set_maxDamage( int mD);
        
        void set_maxRandge(int mD);
        void attack(Vector2D &dir, float delta);

}; 



#endif //CSCI437_WEAPON_H

