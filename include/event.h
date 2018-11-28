#ifndef CSCI437_EVENT_H
#define CSCI437_EVENT_H

typedef long long EventType;

class Event {

public:
    Event() = default;
    ~Event() = default;
    virtual const EventType& getEventType() const = 0;

};

#endif //CSCI437_EVENT_H