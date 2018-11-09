#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include "event.h"
#include "entity.h"

class Player: public Entity{

    private: 
        int health;
        int mana;
        //std::shared_ptr<PlayerData> PlayerData;

    public: 
		Player(float x, float y, float size);

        ~Player();
		void update(double deltaMs) {};

        //handles events 
        void HandleEvents( Event* event);
        ///if eventid = "walk"

        int get_health(){return health;}

        void move(Direction dir, float delta);

}; 

#endif //CSCI437_PLAYER_H