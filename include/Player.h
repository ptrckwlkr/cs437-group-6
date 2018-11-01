#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include "event.h"

class Player {

    private: 

    public: 

    Player();

    ~Player();
    virtual void update(double deltaMs) = 0;
    //virtual ComponentId getComponentId() = 0;

    //handles events 
    void HandleEvents( Event* event);
    ///if eventid = "walk"

}; 

#endif //CSCI437_PLAYER_H