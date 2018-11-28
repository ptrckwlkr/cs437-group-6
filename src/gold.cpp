#include "EventManager.h"
#include "gold.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  type = TYPE_GOLD;

  EventManager::Instance()->registerEvent(EventGoldCollection::eventType, this, &handleGoldCollection);
  EventManager::Instance()->registerEvent(EventCollision::eventType, this, &handleCollision);
}

void Gold::handleGoldCollection(const EventGoldCollection &event)
{
  if (event.getGold().id == id)
  {
    printf("Hello World!\n");
    EventManager::Instance()->unregister(EventGoldCollection::eventType, this);
    EventManager::Instance()->UnregisterObject(EVENT_GOLD_COLLECTION, this);
  }
}

void Gold::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().get_type() == TYPE_PLAYER)
  {
    auto e = EventGoldCollection(this);
    EventManager::Instance()->send(e);
  }
}
