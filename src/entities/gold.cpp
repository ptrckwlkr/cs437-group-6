#include "entities/gold.h"
#include "entities/money.h"
#include "EntityManager.h"

Gold::Gold(float x, float y) : Entity(x, y, GOLD_SIZE)
{
  EventManager::Instance().registerListener(EventCollision::eventType, this, &Gold::handleCollision);
}

void Gold::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
  {
    auto e = EventGoldCollection(this);
    EventManager::Instance().sendEvent(e);
    EntityManager::Instance().removeEntity(id);
    EntityManager::Instance().createEntity<Money>(pos.x, pos.y);
  }
}
