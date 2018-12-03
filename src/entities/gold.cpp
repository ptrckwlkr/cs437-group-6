#include "entities/gold.h"
#include "EntityManager.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  EventManager::Instance().registerListener(EventGoldCollection::eventType, this, &Gold::handleGoldCollection);
  EventManager::Instance().registerListener(EventCollision::eventType, this, &Gold::handleCollision);
}


void Gold::handleGoldCollection(const EventGoldCollection &event)
{
  if (event.getGold().id == id)
  {
    EntityManager::Instance().removeEntity(id);
  }
}

void Gold::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
  {
    auto e = EventGoldCollection(this);
    EventManager::Instance().sendEvent(e);
  }
}
