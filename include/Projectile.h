#ifndef CSCI437_PROJECTILE_H
#define CSCI437_PROJECTILE_H

#include "entity.h"
#include "event.h"
#include "math.h"
#include "SFML/System.hpp"

class Projectile: public Entity
{

    private: 
    int maxDamage;
    int curDamage;
    int maxRange;
    int speed;

    protected:
    sf::Vector2f velocity;
    sf::Vector2f playerCenter;
    sf::Vector2f mousePos;
    sf::Vector2f aimDirection;
    sf::Vector2f aimDirectionNormal;


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

        void set_velocity( const sf::Vector2f velocity);

        void set_mousePos( sf::Vector2f &mPos);

        void set_playerCenter( sf::Vector2f &pCenter);

        void set_aimDirection ();

        sf::Vector2f set_aimDirectionNormal();

        void move(Vector2D &dir, float delta);

        void attack(Vector2D &dir, float delta);

}; 



#endif //CSCI437_WEAPON_H

