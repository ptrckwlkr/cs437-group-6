#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include "event.h"
#include "entity.h"
#include "listener.h"

class Player: public Entity
{

    private: 
        int health;
        int mana;
        //std::shared_ptr<PlayerData> PlayerData;
public:
		Player(float x, float y, float size);

		~Player();
		void update(double delta) {};

		void move(Vector2D &dir, float delta);
		void animate() {};
		void HandleEvent(Event* event);

}; 

#endif //CSCI437_PLAYER_H