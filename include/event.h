#ifndef CSCI437_EVENT_H
#define CSCI437_EVENT_H

#include <string>
using std::string;

enum EVENTID
{
    EVENT_COLLISION,
    EVENT_GOLD_COLLECTION,
};

class Event {

private:
    //contains these elements
    EVENTID eventId;
    void* arg1;


public: 
    Event(EVENTID eventId, void* arg1 = 0){
        this->eventId = eventId;
        this->arg1 = arg1;

    }
    ~Event(){}

    inline EVENTID EventId() const {return eventId;}
    inline void* Arg1(){ return arg1; }
    

};

#endif //CSCI437_EVENT_H