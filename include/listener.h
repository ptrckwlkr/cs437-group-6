#ifndef CSCI437_LISTENER_H
#define CSCI437_LISTENER_H

#include "event.h"

class Listener {
    public: 

        //Constructor
        Listener() {}
        virtual ~Listener() {}

        //need to call an event class 
        virtual void HandleEvent( Event* event) = 0; 

};

#endif //CSCI437_LISTENER_H
