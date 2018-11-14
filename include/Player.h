#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include "event.h"
#include "entity.h"
#include "Projectile.h"
#include "listener.h"

class Player: public Entity
{

    private: 
        int health = 20;
        int mana;
        //std::shared_ptr<PlayerData> PlayerData;
		std::shared_ptr<Projectile> projectile;
public:
		Player(float x, float y, float size);

		~Player();
		void update(double delta) {};

		void set_projectile(std::shared_ptr<Projectile>  p);
		std::shared_ptr<Projectile> get_projectile(){return projectile;}
		void move(Vector2D &dir, float delta);
		void animate() {};
		void HandleEvent(Event* event);

}; 

#endif //CSCI437_PLAYER_H