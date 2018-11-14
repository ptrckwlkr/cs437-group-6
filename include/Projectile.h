#ifndef CSCI437_PROJECTILE_H
#define CSCI437_PROJECTILE_H

#include "entity.h"
#include "event.h"
#include "math.h"
#include "SFML/System.hpp"
#include "vector2d.h"

class Projectile: public Entity
{

    private: 
    int maxDamage;
    int curDamage;
    int maxRange;
    int speed;

    protected:
    Vector2D velocity = VEC_NONE;
    Vector2D playerCenter= VEC_NONE;
    Vector2D  mousePos = VEC_NONE;
    Vector2D aimDirection = VEC_NONE;



    public: 
        Projectile(float x, float y, float size);

        ~Projectile();
        virtual void update(double deltaMs) {};

        //handles events 
        virtual void HandleEvent( Event* event);
        ///if eventid = "attack"

        void set_maxDamage( int mD);
        
        void set_maxRange(int mD);

        void set_speed ( int speed);

        void set_velocity(  Vector2D &vel);

        void set_mousePos(  Vector2D  &mPos);

        void set_playerCenter(  Vector2D  &pCenter);

        void set_aimDirection ();

        Vector2D  get_aimDireciton(){ return aimDirection;}

        //sf::Vector2f set_aimDirectionNormal();

        void move(Vector2D &dir, float delta);

        void attack(Vector2D &dir, float delta);

}; 



#endif //CSCI437_WEAPON_H

