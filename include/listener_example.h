
#ifndef CSCI437_LISTENEREXAMPLE_H
#define CSCI437_LISTENEREXAMPLE_H

#include "event.h"
#include "listener.h"

class ListenerExample : public Listener{
    private:

    int x; 
    int y;
    int color;
    int pic; 

    public:
    ListenerExample( int x =100, int y=100);
    ~ListenerExample();
    void HandleEvent( Event* event);

    void Render(); //draw the objects 

};

#endif //CSCI437_LISTENEREXAMPLE_H