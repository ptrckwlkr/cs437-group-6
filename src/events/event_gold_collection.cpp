#include <entity.h>
#include "events/event_gold_collection.h"

const EventType EventGoldCollection::eventType = 4;//(EventType)(&EventGoldCollection::eventType);

EventGoldCollection::EventGoldCollection(Gold *gold) : Event(), gold(gold)
{

}
