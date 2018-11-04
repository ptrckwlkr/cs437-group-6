#include "listener_example.h"

ListenerExample::ListenerExample(int x, int y ){
    this->x =x;
    this->y = y; 

}

void ListenerExample::HandleEvent(Event* event){
    if ( event->EventId() == "WALK DOWN"){
        y -= 10.0f; 
    }

    else if ( event->EventId() == "JUMP"){
        x += 10.0f; 

    }

}

void ListenerExample::Render(){
    //draw the objects,  possible class the a draw method 
} 





