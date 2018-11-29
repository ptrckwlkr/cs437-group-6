#include <EntityManager.h>
#include "EventManager.h"
#include "entities/gold.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  type = TYPE_GOLD;

  EventManager::Instance()->registerListener(EventGoldCollection::eventType, this, &handleGoldCollection);
  EventManager::Instance()->registerListener(EventCollision::eventType, this, &handleCollision);
}

Gold::~Gold()
{

}

void Gold::handleGoldCollection(const EventGoldCollection &event)
{
  if (event.getGold().id == id)
  {
    printf("Gold Collected!\n");
    EventManager::Instance()->unregisterListener(EventGoldCollection::eventType, this);
    EntityManager::Instance()->removeEntity(id);
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
