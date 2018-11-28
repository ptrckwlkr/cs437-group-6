#include "EventManager.h"
#include "gold.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  type = TYPE_GOLD;
  EventManager::Instance()->RegisterObject(EVENT_GOLD_COLLECTION, this);

  //EventDelegate delegate = std::bind(&Gold::handle, this, std::placeholders::_1);
  //EventManager::Instance()->registerEvent(EventGoldCollection::eventType, delegate);
  EventManager::Instance()->registerEvent(EventGoldCollection::eventType, this, &handle);
}

void Gold::handle(const EventGoldCollection &event)
{
  if (event.getGold().id == id)
  {
    printf("Hello World!\n");
    EventManager::Instance()->unregister(EventGoldCollection::eventType, this);
    EventManager::Instance()->UnregisterObject(EVENT_GOLD_COLLECTION, this);
  }
}
