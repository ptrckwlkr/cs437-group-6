#include <EventManager.h>
#include "gold.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  EventManager::Instance()->RegisterObject(COLLISION_EVENT, this);
}

void Gold::HandleEvent(Event *event)
{
  if (event->EventId() == COLLISION_EVENT)
  {
    printf("Collected gold!\n");
    EventManager::Instance()->UnregisterObject(COLLISION_EVENT, this);
  }
}
