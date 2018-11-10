#include "EventManager.h"
#include "gold.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  type = TYPE_GOLD;
  EventManager::Instance()->RegisterObject(EVENT_GOLD_COLLECTION, this);
}

void Gold::HandleEvent(Event *event)
{
  if (event->EventId() == EVENT_GOLD_COLLECTION)
  {
    printf("GOLD: I have been collected!\n");
    EventManager::Instance()->UnregisterObject(EVENT_GOLD_COLLECTION, this);
  }
}
