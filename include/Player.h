#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include <memory>
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

public:
		Player(float x, float y);

		~Player();
		void update(double delta) {};
		void attack(Vector2D &dir);
		void HandleEvent(Event* event) override;

}; 

#endif //CSCI437_PLAYER_H
