#ifndef CSCI437_EVENT_H
#define CSCI437_EVENT_H

#include <string>

typedef long long EventType;

using std::string;

enum EVENTID
{
    EVENT_COLLISION,
    EVENT_GOLD_COLLECTION,
    EVENT_PLAYER_SHOOT_AT,
    EVENT_ENEMY_SHOT_AT,
};

class Event {

public:
    Event() = default;
    ~Event() = default;
    inline EVENTID EventId() const {return EVENT_ENEMY_SHOT_AT;}
    virtual const EventType& getEventType() const = 0;

};

#endif //CSCI437_EVENT_H