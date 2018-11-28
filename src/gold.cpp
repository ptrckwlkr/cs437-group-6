#include "EventManager.h"
#include "gold.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  type = TYPE_GOLD;

  EventManager::Instance()->registerEntity(EventGoldCollection::eventType, this, &handleGoldCollection);
  EventManager::Instance()->registerEntity(EventCollision::eventType, this, &handleCollision);
}

void Gold::handleGoldCollection(const EventGoldCollection &event)
{
  if (event.getGold().id == id)
  {
    printf("Gold Collected!\n");
    EventManager::Instance()->unregisterObject(EventGoldCollection::eventType, this);
  }
}

void Gold::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().get_type() == TYPE_PLAYER)
  {
    auto e = EventGoldCollection(this);
    EventManager::Instance()->sendEvent(e);
  }
}
