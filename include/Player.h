#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include "event.h"
#include "entity.h"

class Player: public Entity
{

private:
		int health;
		int mana;

public:
		Player(float x, float y, float size);

		~Player();
		void update(double deltaMs) {};

		//handles events
		void HandleEvents(Event* event);
		///if eventid = "walk"

		void move(Direction dir, float delta);
		void animate() {};

}; 

#endif //CSCI437_PLAYER_H