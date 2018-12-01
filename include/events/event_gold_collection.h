#ifndef CSCI437_EVENT_GOLD_COLLECTION_H
#define CSCI437_EVENT_GOLD_COLLECTION_H

#include "event.h"

class Gold;
class EventGoldCollection : public Event
{

public:
    explicit EventGoldCollection(Gold *gold) : Event(), gold(gold) {}
    static const EventType eventType;
    const EventType& getEventType() const override {return eventType;}
    Gold &getGold() const {return *gold;}

private:
    Gold *gold;

};


#endif //CSCI437_EVENT_GOLD_COLLECTION_H
